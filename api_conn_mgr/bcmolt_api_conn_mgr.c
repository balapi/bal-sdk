/*
<:copyright-BRCM:2016-2020:Apache:standard

 Copyright (c) 2016-2020 Broadcom. All Rights Reserved

 The term “Broadcom” refers to Broadcom Inc. and/or its subsidiaries

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

:>
 */

#include <bcmos_system.h>
#include <bcmolt_api_conn_mgr.h>
#include <bcmolt_api.h>
#include <bcmolt_api_model.h>
#include <bcmolt_msg.h>
#include <bcmtr_interface.h>
#include <bcm_dev_log.h>
#include <bcmolt_api_topology.h>
#include <bcmolt_api_translation.h>
#include <bcmolt_host_sw_version.h>
#include <bcmolt_api_model_revision.h>

typedef struct conn_mgr_inst
{
    bcmtr_conn_parms tr_conn_parms; /* Connection parameters */
    uint16_t conn_id;           /* Unique connection id. Randomly assigned when trmux starts */
    uint16_t num_failures;      /* Number of consecutive keep-alive failures */
    bcmos_sem init_sem;         /* Semaphore for startup synchronization */
    bcmos_task ka_task;         /* Keep alive task */
    bcmos_bool ka_task_created; /* TRUE = task created */
    bcmolt_goid olts[BCM_MAX_OLTS_PER_LINE_CARD];
    bcmolt_gdid devices[BCM_MAX_DEVS_PER_LINE_CARD];
    bcmos_bool connected;       /* TRUE=connected */
    bcmolt_api_conn_mgr_flags flags;
} conn_mgr_inst;

typedef struct conn_mgr_ref
{
    conn_mgr_inst *cm;
    bcmolt_goid olt;
    bcmolt_loid loid;
} conn_mgr_ref;

/* Max number of OLTs can't exceed the total number of supported devices */
static conn_mgr_ref conn_mgr_ref_array[BCM_MAX_OLTS];

/* Connect/Disconnect notification subscription */
typedef struct conn_mgr_subscriber conn_mgr_subscriber;
struct conn_mgr_subscriber
{
    F_api_conn_mgr_connect_disconnect_ind cb;     /* Subscriber's callback */
    STAILQ_ENTRY(conn_mgr_subscriber) next;
};
static STAILQ_HEAD(conn_mgr_subscriber_list, conn_mgr_subscriber) subscriber_list;
static bcmos_mutex subscriber_lock;
static void _api_conn_mgr_connect_disconnect_notify(bcmolt_goid olt, bcmolt_api_conn_status status,
    bcmolt_olt_disconnect_reason reason);
static bcmos_bool conn_mgr_initialized;

#if ENABLE_LOG
static dev_log_id conn_mgr_log_id[BCM_MAX_OLTS];

#define CONN_MGR_LOG(olt, level, fmt, ...) \
    BCM_LOG(level, conn_mgr_log_id[olt], fmt, ## __VA_ARGS__)
#else
#define CONN_MGR_LOG(olt, level, fmt, ...) \
    do \
    { \
    } while (0)
#endif

/* Polling interval when waiting for connection with the core */
#define CM_WAIT_FOR_CONNECTION_INTERVAL_US     100000

/* Max time to wait until connection manager starts */
#define CM_WAIT_FOR_INIT_INTERVAL_US           2000000

/* Interval between KA messages when connected */
#define CM_KEEP_ALIVE_INTERVAL_US              1000000

/* Max number of keep-alive messages that can be missed before disconnect is declared */
#define CM_KEEP_ALIVE_MAX_MISS                 3

/* Install indication handlers for all devices on the OLT that just connected */
static bcmos_errno _api_conn_mgr_handler_register_install(bcmolt_goid olt)
{
    conn_mgr_inst *cm = conn_mgr_ref_array[olt].cm;
    bcmolt_odid odid;
    bcmolt_ldid ldid;
    bcmolt_gdid gdid;
    bcmos_errno err = BCM_ERR_OK;

    if (cm == NULL)
        return BCM_ERR_NOT_CONNECTED;

    for (odid = 0;
        bcmolt_apitopo_odid_to_gdid_ldid(olt, odid, &gdid, &ldid) == BCM_ERR_OK;
        odid++)
    {
        bcmos_bool transport_connected = BCMOS_FALSE;
        bcmtr_is_connected(gdid, &transport_connected);
        if (!transport_connected)
        {
            bcmtr_conn_parms conn_parms = cm->tr_conn_parms;
            conn_parms.ldid = ldid;
            err = bcmtr_connect(gdid, &conn_parms);
        }
        err = err ? err : bcmtr_msg_handler_register_install(gdid);
        if (err != BCM_ERR_OK)
            break;
    }

    return err;
}

/* Read topology */
static bcmos_errno _api_conn_mgr_topo_read(bcmolt_goid olt, bcmolt_topology *topo, bcmolt_host_sw_version *sw_version)
{
    conn_mgr_ref *ref = &conn_mgr_ref_array[olt];
    conn_mgr_inst *cm = ref->cm;
    bcmolt_olt_cfg olt_cfg;
    bcmolt_olt_key key = {};
    bcmos_bool connected = cm->connected;
    bcmos_errno err;

    /* Set up temporary translation to keep API translation layer happy.
       It doesn't really matter how device is mapped when querying OLT object.
     */
    /* Create GOID - LOID mapping */
    err = bcmolt_apitopo_goid_to_loid_set(cm->devices[0], olt, ref->loid);
    err = err ? err : bcmolt_apitopo_odid_to_gdid_set(olt, 0, cm->devices[0]);
    if (err != BCM_ERR_OK)
    {
        CONN_MGR_LOG(olt, ERROR, "Can't create temporary topology mapping, %s\n", bcmos_strerror(err));
        bcmolt_apitopo_olt_clear(olt);
        return err;
    }

    /* Read topology */
    cm->connected = BCMOS_TRUE;
    BCMOLT_CFG_INIT(&olt_cfg, olt, key);
    BCMOLT_FIELD_SET_PRESENT(&olt_cfg.data, olt_cfg_data, topology);
    BCMOLT_FIELD_SET_PRESENT(&olt_cfg.data, olt_cfg_data, host_sw_version);
    BCMOLT_CFG_LIST_BUF_SET(&olt_cfg, olt, topo->topology_maps.arr, sizeof(bcmolt_topology_map) * topo->topology_maps.len);
    err = bcmolt_cfg_get(olt, &olt_cfg.hdr);
    cm->connected = connected;

    /* Clear temporary OLT mapping. Translation layer will create a real one */
    bcmolt_apitopo_olt_clear(olt);

    if (err == BCM_ERR_OK)
    {
        *topo = olt_cfg.data.topology;
        *sw_version = olt_cfg.data.host_sw_version;
    }
    else
    {
        /* OLT agent can be located on aspen, outside management daemon.
           In this case this bcmolt_cfg_get() will return BCM_ERR_NOT_CONNECTED and we should
           revert to hardcoded single device topology
           - ldid == loid
           - odid = 0
           - pif == lif for max number of interfaces supported by device
         */
        if (err == BCM_ERR_TIMEOUT)
        {
            int i;
            topo->topology_maps.len = BCM_MAX_PONS_PER_DEV;
            for (i = 0; i < topo->topology_maps.len; i++)
            {
                topo->topology_maps.arr[i].local_device_id = ref->loid;
                topo->topology_maps.arr[i].olt_device_id = 0;
                topo->topology_maps.arr[i].physical_if_id = i;
            }
            err = BCM_ERR_OK;
        }
    }

    return err;
}

/* Handle "connected" status change for a single OLT */
static bcmos_errno _api_conn_mgr_handle_connect(bcmolt_goid olt)
{
    conn_mgr_ref *ref = &conn_mgr_ref_array[olt];
    conn_mgr_inst *cm = ref->cm;
    bcmolt_topology_map topo_map[BCM_MAX_PONS_PER_OLT] = {};
    bcmolt_topology topo = { .topology_maps = { .len = BCM_MAX_PONS_PER_OLT, .arr = &topo_map[0] } };
    bcmolt_host_sw_version sw_version = {};
    bcmos_errno err;

    /* Handle possible race */
    if (cm == NULL)
        return BCM_ERR_OK;

    do
    {
        /* Read topology */
        err = _api_conn_mgr_topo_read(olt, &topo, &sw_version);
        if (err != BCM_ERR_OK)
        {
            if (err == BCM_ERR_RANGE)
                CONN_MGR_LOG(olt, INFO, "Logical OLT %u doesn't exist\n", olt);
            else
                CONN_MGR_LOG(olt, ERROR, "Failed to read OLT topology. %s\n", bcmos_strerror(err));
            break;
        }

        /* Initialize translation layer */
        err = bcmolt_api_translate_olt_init(olt, ref->loid, cm->devices, &topo);
        if (err != BCM_ERR_OK)
        {
            CONN_MGR_LOG(olt, ERROR, "bcmolt_api_translate_olt_init() -> %s\n", bcmos_strerror(err));
            break;
        }

        /* Install indication handlers */
        err = _api_conn_mgr_handler_register_install(olt);
        if (err != BCM_ERR_OK)
        {
            /* Failed to update subscriptions in the core. The error is already logged */
            CONN_MGR_LOG(olt, INFO, "Failed to update subscriptions in device management daemon\n");
            break;
        }

        /* Report 'connected' event to all subscribers */
        _api_conn_mgr_connect_disconnect_notify(olt, BCMOLT_API_CONN_STATUS_CONNECTED,
            BCMOLT_OLT_DISCONNECT_REASON_CONNECTED);
    } while (0);

    if (err != BCM_ERR_OK)
    {
        bcmolt_apitopo_olt_clear(olt);
        return err;
    }

    CONN_MGR_LOG(olt, INFO,
        "Connected with OLT %u. Software version: %u.%u.%u. Model revision: %u. Build time: %s\n",
        olt, sw_version.major, sw_version.minor, sw_version.revision, sw_version.model,
        (sw_version.build_time.str != NULL) ? sw_version.build_time.str : "unknown");
    if (sw_version.major != BCMOLT_HOST_MAJOR_VER ||
        sw_version.minor != BCMOLT_HOST_MINOR_VER ||
        sw_version.revision != BCMOLT_HOST_REVISION_VER ||
        sw_version.model != BCMOLT_MODEL_REVISION)
    {
        CONN_MGR_LOG(olt, WARNING,
            "OLT %u: Software version mismatch: application software version: %u.%u.%u. Model revision: %u\n",
            olt, BCMOLT_HOST_MAJOR_VER, BCMOLT_HOST_MINOR_VER, BCMOLT_HOST_REVISION_VER, BCMOLT_MODEL_REVISION);
    }

    return BCM_ERR_OK;
}

/* Handle "disconnected" status change for a single OLT */
static bcmos_errno _api_conn_mgr_handle_disconnect(bcmolt_goid olt, bcmolt_olt_disconnect_reason reason)
{
    conn_mgr_inst *cm = conn_mgr_ref_array[olt].cm;
    bcmolt_odid odid;
    bcmolt_ldid ldid;
    bcmolt_gdid gdid;

    /* Handle possible race */
    if (cm == NULL)
        return BCM_ERR_OK;

    CONN_MGR_LOG(olt, ERROR, "Lost connection with OLT %u.\n", olt);

    /* Report 'disconnected' event to all subscribers */
    _api_conn_mgr_connect_disconnect_notify(olt, BCMOLT_API_CONN_STATUS_DISCONNECTED, reason);

    /* Disconnect transport */
    for (odid = 0;
        bcmolt_apitopo_odid_to_gdid_ldid(olt, odid, &gdid, &ldid) == BCM_ERR_OK;
        odid++)
    {
        bcmos_bool transport_connected = BCMOS_FALSE;
        bcmtr_is_connected(gdid, &transport_connected);
        if (transport_connected)
        {
            bcmtr_disconnect(gdid);
        }
    }

    /* Clean-up OLT topology */
    bcmolt_api_translate_olt_exit(olt);

    return BCM_ERR_OK;
}

/* Generate olt.state_changed indication */
static bcmos_errno _api_conn_mgr_send_status_change(conn_mgr_inst *cm, bcmos_bool connected,
    bcmolt_olt_disconnect_reason reason)
{
    bcmos_errno err = BCM_ERR_OK;
    bcmolt_loid l;

    for (l = 0; l < BCM_MAX_OLTS_PER_LINE_CARD && err == BCM_ERR_OK; l++)
    {
        if (cm->olts[l] == BCMOLT_GOID_UNDEFINED)
            continue;

        if (connected)
        {
            err = _api_conn_mgr_handle_connect(cm->olts[l]);
        }
        else
        {
            _api_conn_mgr_handle_disconnect(cm->olts[l], reason);
        }
    }

    /* Ignore range error. It just means that some logical OLTs are not present in device management daemon topology */
    if (err == BCM_ERR_RANGE)
        err = BCM_ERR_OK;

    return err;
}

/* Per-core connection manager keep-alive task handler */
static int _api_conn_mgr_task_handler(long data)
{
    conn_mgr_inst *cm = (conn_mgr_inst *)data;
    uint16_t conn_id;
    bcmos_bool just_started = BCMOS_TRUE;
    bcmos_bool new_conn_state;
    uint32_t delay;
    bcmolt_ldid d;

    while (!cm->ka_task.destroy_request)
    {
        bcmos_errno err = BCM_ERR_OK;

        /* If transport is not connected - try to connect */
        for (d = 0; d < BCM_MAX_DEVS_PER_LINE_CARD && err == BCM_ERR_OK; d++)
        {
            if (cm->devices[d] != BCMOLT_GDID_UNDEFINED)
            {
                bcmos_bool transport_connected = BCMOS_FALSE;
                bcmtr_is_connected(cm->devices[d], &transport_connected);
                if (!transport_connected)
                {
                    bcmtr_conn_parms conn_parms = cm->tr_conn_parms;
                    conn_parms.ldid = d;
                    err = bcmtr_connect(cm->devices[d], &conn_parms);
                }
            }
        }

        /* Send keep-alive query */
        conn_id = cm->conn_id;
        if ((cm->flags & BCMOLT_API_CONN_MGR_FLAGS_DISABLE_KA) == 0)
            err = err ? err : bcmtr_keep_alive(cm->devices[0], &conn_id);
        new_conn_state = (err == BCM_ERR_OK);

        /* Reset KA failure counter if KA was successful */
        if (new_conn_state)
            cm->num_failures = 0;
        else
            ++cm->num_failures;

        /* Handle state changes */
        if (new_conn_state != cm->connected || conn_id != cm->conn_id)
        {
            /* Send status_change indication if core disconnected or if conn_id changed.
             * conn_id change means that core has been restarted.
             */
            if (cm->connected &&
                ((cm->num_failures >= CM_KEEP_ALIVE_MAX_MISS) || (conn_id != cm->conn_id)))
            {
                /* Failed once too many times or conn_id changed */
                _api_conn_mgr_send_status_change(cm, BCMOS_FALSE,
                    (conn_id != cm->conn_id) ? BCMOLT_OLT_DISCONNECT_REASON_DAEMON_RESTART : BCMOLT_OLT_DISCONNECT_REASON_KA_FAILURE);
                cm->connected = BCMOS_FALSE;
            }

            /* If core just got connected
             * - update registrations
             * - send status_change indication
             */
            if (!cm->connected && new_conn_state)
            {
                cm->conn_id = conn_id;
                /* Handle status change. Do NOT update state if failed. May be next iteration will go better */
                err = _api_conn_mgr_send_status_change(cm, new_conn_state, BCMOLT_OLT_DISCONNECT_REASON_CONNECTED);
                if (err == BCM_ERR_OK)
                {
                    cm->connected = new_conn_state;
                }
            }
        }

        /* If just started - notify init task */
        if (just_started)
        {
            bcmos_sem_post(&cm->init_sem);
            just_started = BCMOS_FALSE;
        }

        /* Keep polling */
        delay = cm->connected ? CM_KEEP_ALIVE_INTERVAL_US : CM_WAIT_FOR_CONNECTION_INTERVAL_US;
        bcmos_usleep(delay);
    }
    cm->ka_task.destroyed = BCMOS_TRUE;

    return 0;
}

/* Find instance with matching address */
static conn_mgr_inst *_api_conn_mgr_inst_find(const bcmtr_conn_parms *tr_conn_parms)
{
    bcmolt_goid olt;
    for (olt = 0; olt < BCM_MAX_OLTS; olt++)
    {
        if (conn_mgr_ref_array[olt].cm &&
            conn_mgr_ref_array[olt].cm->tr_conn_parms.type == tr_conn_parms->type &&
            !memcmp(&conn_mgr_ref_array[olt].cm->tr_conn_parms.x, &tr_conn_parms->x, sizeof(tr_conn_parms->x)))
        {
            return conn_mgr_ref_array[olt].cm;
        }
    }
    return NULL;
}

static void _api_conn_mgr_init(void)
{
    if (conn_mgr_initialized)
        return;
    conn_mgr_initialized = BCMOS_TRUE;
    bcmos_mutex_create(&subscriber_lock, 0, "conn_mgr_ind");
    STAILQ_INIT(&subscriber_list);
}

/* Start API connection manager for an OLT */
bcmos_errno bcmolt_api_conn_mgr_start(bcmolt_goid olt, bcmolt_loid loid,
    const bcmtr_conn_parms *tr_conn_parms, bcmolt_api_conn_mgr_flags flags)
{
    bcmos_task_parm task_p =
    {
        .priority = TASK_PRIORITY_KEEP_ALIVE,
        .handler = _api_conn_mgr_task_handler
    };
    char task_name[32];
    conn_mgr_inst *cm;
    conn_mgr_ref *ref = &conn_mgr_ref_array[olt];
    bcmolt_loid l;
    bcmolt_ldid d;
    bcmos_errno err;

    _api_conn_mgr_init();

    if (olt >= BCM_MAX_OLTS || loid >= BCM_MAX_OLTS_PER_LINE_CARD || tr_conn_parms == NULL)
        return BCM_ERR_PARM;

    if (ref->cm != NULL)
        return BCM_ERR_ALREADY;

#ifdef ENABLE_LOG
    if (!conn_mgr_log_id[olt] || conn_mgr_log_id[olt] == DEV_LOG_INVALID_ID)
    {
        char name[32];
        snprintf(name, sizeof(name)-1, "API_KA_%u", olt);
        conn_mgr_log_id[olt] = bcm_dev_log_id_register(name, DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
        if (conn_mgr_log_id[olt] == DEV_LOG_INVALID_ID)
        {
            BCMOS_TRACE_ERR("Can't create a log");
            return BCM_ERR_INTERNAL;
        }
    }
#endif

    ref->olt = olt;
    ref->loid = loid;

    /* Look for existing instance at the same address */
    cm = _api_conn_mgr_inst_find(tr_conn_parms);
    if (cm != NULL)
    {
        if (cm->olts[loid] != BCMOLT_GOID_UNDEFINED)
        {
            CONN_MGR_LOG(olt, ERROR, "Can's start CM for OLT %u. LOID %u is already referenced by OLT %u\n",
                olt, loid, cm->olts[loid]);
            return BCM_ERR_INTERNAL;
        }
        conn_mgr_ref_array[olt].cm = cm;
        cm->olts[loid] = olt;
        if (cm->connected)
            _api_conn_mgr_handle_connect(olt);
        return BCM_ERR_OK;
    }

    /* New instance */
    cm = bcmos_calloc(sizeof(conn_mgr_inst));
    if (!cm)
    {
        return BCM_ERR_NOMEM;
    }

    err = bcmos_sem_create(&cm->init_sem, 0, 0, "conn_mgr_init");
    if (err != BCM_ERR_OK)
    {
        bcmos_free(cm);
        return err;
    }

    for (l = 0; l < BCM_MAX_OLTS_PER_LINE_CARD; l++)
        cm->olts[l] = BCMOLT_GOID_UNDEFINED;
    for (d = 0; d < BCM_MAX_DEVS_PER_LINE_CARD; d++)
        cm->devices[d] = BCMOLT_GDID_UNDEFINED;

    /* Allocate new gdid */
    err = bcmolt_apitopo_gdid_alloc(&cm->devices[0]);
    if (err != BCM_ERR_OK)
    {
        CONN_MGR_LOG(olt, ERROR, "Can's allocate GDID\n");
        bcmos_sem_destroy(&cm->init_sem);
        bcmos_free(cm);
        return err;
    }

    err = bcmolt_apitopo_gdid_to_ldid_set(cm->devices[0], 0);
    if (err != BCM_ERR_OK)
    {
        CONN_MGR_LOG(olt, ERROR, "Can's allocate MAP gdid to LDID 0\n");
        bcmolt_apitopo_gdid_free(cm->devices[0]);
        bcmos_sem_destroy(&cm->init_sem);
        bcmos_free(cm);
        return err;
    }

    cm->tr_conn_parms = *tr_conn_parms;
    cm->tr_conn_parms.mode = BCMOLT_CONN_TYPE_MASK_APP;

    cm->connected = BCMOS_FALSE;
    cm->flags = flags;
    ref->cm = cm;
    cm->olts[loid] = olt;

    /* Create keep-alive task */
    task_p.data = (long)cm;
    snprintf(task_name, sizeof(task_name)-1, "api_conn_mgr_%u", olt);
    task_p.name = task_name;
    err = bcmos_task_create(&cm->ka_task, &task_p);
    if (err != BCM_ERR_OK)
    {
        bcmolt_api_conn_mgr_stop(olt);
        return err;
    }
    cm->ka_task_created = BCMOS_TRUE;

    /* Wait for connection manager thread to start and query core for the 1st time */
    err = bcmos_sem_wait(&cm->init_sem, CM_WAIT_FOR_INIT_INTERVAL_US);
    if (err != BCM_ERR_OK)
    {
        CONN_MGR_LOG(olt, ERROR, "Connection manager for olt %u failed to start\n", olt);
        bcmolt_api_conn_mgr_stop(olt);
    }

    return err;
}

/* Check whether connection manager instance is referenced */
static bcmos_bool _api_conn_mgr_is_inst_referenced(conn_mgr_inst *cm)
{
    bcmolt_loid l;
    for (l = 0; l < BCM_MAX_OLTS_PER_LINE_CARD; l++)
    {
        if (cm->olts[l] != BCMOLT_GOID_UNDEFINED)
            return BCMOS_TRUE;
    }
    return BCMOS_FALSE;
}

/* Stop API connection manager for an OLT */
void bcmolt_api_conn_mgr_stop(bcmolt_goid olt)
{
    conn_mgr_ref *cm_ref = &conn_mgr_ref_array[olt];
    conn_mgr_inst *cm;
    bcmolt_ldid d;

    if (olt >= BCM_MAX_OLTS)
        return;
    cm = cm_ref->cm;
    if (cm == NULL)
        return;
    if (cm->connected)
        _api_conn_mgr_handle_disconnect(cm_ref->olt, BCMOLT_OLT_DISCONNECT_REASON_CONNECTED);
    cm->olts[cm_ref->loid] = BCMOLT_GOID_UNDEFINED;
    cm_ref->cm = NULL;

    /* Don't destroy conn_mgr instance if it is still referenced */
    if (_api_conn_mgr_is_inst_referenced(cm))
        return;
    if (cm->ka_task_created)
        bcmos_task_destroy(&cm->ka_task);
    bcmos_sem_destroy(&cm->init_sem);
    for (d = 0; d < BCM_MAX_DEVS_PER_LINE_CARD; d++)
    {
        if (cm->devices[d] != BCMOLT_GDID_UNDEFINED)
        {
            bcmtr_disconnect(cm->devices[d]);
            bcmolt_apitopo_gdid_free(cm->devices[d]);
        }
    }
    bcmos_free(cm);
}

/* Check if OLT is connected */
bcmos_bool bcmolt_api_conn_mgr_is_connected(bcmolt_goid olt)
{
    bcmolt_loid loid;
    /* goid --> loid mapping succeeds only if the connection manager
       is connected to the relevant dev_mgmt_daemon and successfully
       retrieved the OLT topology.
    */
    return (bcmolt_apitopo_goid_to_loid(olt, &loid) == BCM_ERR_OK);
}

void bcmolt_api_conn_mgr_stop_all(void)
{
    bcmolt_goid olt;
    for (olt = 0; olt < BCM_MAX_OLTS; olt++)
    {
        bcmolt_api_conn_mgr_stop(olt);
    }
}

/* Notify connect/disconnect event */
static void _api_conn_mgr_connect_disconnect_notify(bcmolt_goid olt,
    bcmolt_api_conn_status status, bcmolt_olt_disconnect_reason reason)
{
    conn_mgr_subscriber *subs, *tmp;
    STAILQ_FOREACH_SAFE(subs, &subscriber_list, next, tmp)
    {
        subs->cb(olt, status, reason);
    }
}

/* Subscribe to connect/disconnect indication callback.
   Multiple clients can subscribe
*/
bcmos_errno bcmolt_api_conn_mgr_ind_subscribe(F_api_conn_mgr_connect_disconnect_ind cb)
{
    conn_mgr_subscriber *subs = bcmos_calloc(sizeof(conn_mgr_subscriber));

    _api_conn_mgr_init();

    if (!subs)
        return BCM_ERR_NOMEM;

    subs->cb = cb;
    bcmos_mutex_lock(&subscriber_lock);
    STAILQ_INSERT_TAIL(&subscriber_list, subs, next);
    bcmos_mutex_unlock(&subscriber_lock);
    return BCM_ERR_OK;
}

/* Unsubscribe connect/disconnect indication callback.
*/
bcmos_errno bcmolt_api_conn_mgr_ind_unsubscribe(F_api_conn_mgr_connect_disconnect_ind cb)
{
    conn_mgr_subscriber *subs;
    _api_conn_mgr_init();

    bcmos_mutex_lock(&subscriber_lock);
    STAILQ_FOREACH(subs, &subscriber_list, next)
    {
        if (subs->cb == cb)
        {
            STAILQ_REMOVE(&subscriber_list, subs, conn_mgr_subscriber, next);
            bcmos_free(subs);
            break;
        }
    }
    bcmos_mutex_unlock(&subscriber_lock);
    return (subs == NULL) ? BCM_ERR_NOENT : BCM_ERR_OK;
}
