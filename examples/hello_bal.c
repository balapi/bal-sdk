/*
 *  <:copyright-BRCM:2018-2020:Apache:standard
 *
 *   Copyright (c) 2018-2020 Broadcom. All Rights Reserved
 *
 *   The term “Broadcom” refers to Broadcom Inc. and/or its subsidiaries
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *  :>
 *
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <semaphore.h>

#include <bcmolt_host_api.h>
#include <bcmolt_api_metadata.h>

sem_t connect_cb_mutex;
sem_t interface_cb_mutex;

static void user_appl_indication_cb(bcmolt_devid olt, bcmolt_msg *msg);

static int help(const char *cmd)
{
    const char *p;

    while ((p = strchr(cmd, '/')))
    {
        cmd = p + 1;
    }

    fprintf(stderr,
        "%s"
        " [-transport DOMAIN | UDP ip:port]"
        "\n", cmd);
    fprintf(stderr,
            "\t -transport DOMAIN | UDP ip:port - interface between application and device management daemon\n"
           );

    return -EINVAL;

    return -1;
}

/* parse ip:port */
static bcmos_errno _parse_ip_port(const char *s, uint32_t *ip, uint16_t *port)
{
    int n;
    uint32_t ip1, ip2, ip3, ip4, pp;

    n = sscanf(s, "%u.%u.%u.%u:%u", &ip1, &ip2, &ip3, &ip4, &pp);
    if (n != 5 || ip1 > 0xff || ip2 > 0xff || ip3 > 0xff || ip4 > 0xff || pp > 0xffff)
    {
        fprintf(stderr, "Can't parse %s. Must be ip_address:port\n", s);
        return BCM_ERR_PARM;
    }
    *ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
    *port = pp;
    return BCM_ERR_OK;
}

int main(int argc, char *argv[])
{
    bcmos_errno ret;
    bcmolt_host_init_parms init_parms = {};

    do {
        /* Specify a connection to a local dev_mgmt_daemon */
        init_parms.transport.type = BCM_HOST_API_CONN_LOCAL;

        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "-transport"))
            {
                ++i;
                if (i >= argc)
                    return help(argv[0]);
                if (!strcmp(argv[i], "DOMAIN"))
                    init_parms.transport.type = BCM_HOST_API_CONN_LOCAL;
                else if (!strcmp(argv[i], "UDP"))
                {
                    init_parms.transport.type = BCM_HOST_API_CONN_REMOTE;
                    ++i;
                    if (i >= argc)
                        return help(argv[0]);
                    if (_parse_ip_port(argv[i], &init_parms.transport.addr.ip.u32,
                        &init_parms.transport.addr.port) != BCM_ERR_OK)
                    {
                        return help(argv[0]);
                    }
                }
                else
                    return help(argv[0]);
            }
            else
            {
                return help(argv[0]);
            }
        }

        /* Initialize the Broadcom host interface */
        ret = bcmolt_host_init(&init_parms);
        if(BCM_ERR_OK != ret)
        {
            fprintf(stderr, "error detected in call to bcmolt_host_init\n");
            break;
        }
        else
        {
            printf("host initialization success\n");
        }

        /* Reset MAC device 0 */
        bcmolt_device_reset dev_oper_rst;
        bcmolt_odid dev_id = 0;
        bcmolt_device_key dev_key = {.device_id = dev_id};

        BCMOLT_OPER_INIT(&dev_oper_rst, device, reset, dev_key);

        printf("performing reset device %u\n", dev_id);
        ret = bcmolt_oper_submit(dev_id, &dev_oper_rst.hdr);
        if(BCM_ERR_OK != ret)
        {
            fprintf(stderr, "error detected in call to reset device %u (%s) %s\n", dev_id, bcmos_strerror(ret),
                   dev_oper_rst.hdr.hdr.err_text);
            break;
        }
        else
        {
            printf("device reset operation success\n");
        }

        bcmolt_rx_cfg rx_cfg = {};

        rx_cfg.obj_type = BCMOLT_OBJ_ID_DEVICE;
        rx_cfg.flags = BCMOLT_AUTO_FLAGS_NONE;
        rx_cfg.rx_cb = user_appl_indication_cb;

        rx_cfg.subgroup = BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_COMPLETE;
        ret = bcmolt_ind_subscribe(dev_id, &rx_cfg);
        if (ret != BCM_ERR_OK)
        {
            fprintf(stderr, "Failed to subscribe to device connect indications. Error %s\n", bcmos_strerror(ret));
            break;
        }
        else
        {
            printf("Subscribed to device connect indications\n");
        }

        rx_cfg.subgroup = BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_FAILURE;
        ret = bcmolt_ind_subscribe(dev_id, &rx_cfg);
        if (ret != BCM_ERR_OK)
        {
            fprintf(stderr, "Failed to subscribe to device connect failure indications. Error %s\n", bcmos_strerror(ret));
            break;
        }
        else
        {
            printf("Subscribed to device connect-failure indications\n");
        }

        sem_init(&connect_cb_mutex, 0, 0);

        /* Connect device 0 in XGS__2_X mode, and wait for successful completion */
        bcmolt_device_connect dev_oper_conn;

        BCMOLT_OPER_INIT(&dev_oper_conn, device, connect, dev_key);
        BCMOLT_MSG_FIELD_SET(&dev_oper_conn, system_mode, BCMOLT_SYSTEM_MODE_XGS__2_X);

        printf("performing connect device %u\n", dev_id);
        ret = bcmolt_oper_submit(dev_id, &dev_oper_conn.hdr);
        if(BCM_ERR_OK != ret)
        {
            fprintf(stderr, "error detected trying to connect to device %u (%s) %s\n", dev_id, bcmos_strerror(ret),
                   dev_oper_rst.hdr.hdr.err_text);
            sem_destroy(&connect_cb_mutex);
            break;
        }
        else
        {
            printf("device connect operation success\n");

#ifndef BCMOLT_API_STUB

            /* Wait for the connection to successfully complete */
            printf("waiting for connection complete indication...\n");
            sem_wait(&connect_cb_mutex);

#endif /* BCMOLT_API_STUB */

            printf("connection complete\n");
            sem_destroy(&connect_cb_mutex);
        }

        rx_cfg.obj_type = BCMOLT_OBJ_ID_PON_INTERFACE;
        rx_cfg.flags = BCMOLT_AUTO_FLAGS_NONE;
        rx_cfg.rx_cb = user_appl_indication_cb;

        rx_cfg.subgroup = BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_STATE_CHANGE_COMPLETED;
        ret = bcmolt_ind_subscribe(dev_id, &rx_cfg);
        if (ret != BCM_ERR_OK)
        {
            fprintf(stderr, "Failed to subscribe to interface state change indications. Error %s\n",
                    bcmos_strerror(ret));
            break;
        }
        else
        {
            printf("Subscribed to interface state change indications\n");
        }

        /* prepare to bring up PON 0 */
        sem_init(&interface_cb_mutex, 0, 0);

        bcmolt_pon_interface_key intf_key = {.pon_ni = 0};
        bcmolt_pon_interface_set_pon_interface_state pon_interface_set_state;

        BCMOLT_OPER_INIT(&pon_interface_set_state, pon_interface, set_pon_interface_state, intf_key);
        BCMOLT_MSG_FIELD_SET(&pon_interface_set_state, operation, BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING );

        printf("performing pon interface activation\n");
        ret = bcmolt_oper_submit(dev_id, &pon_interface_set_state.hdr);
        if(BCM_ERR_OK != ret)
        {
            fprintf(stderr, "error detected trying to activate pon interface (%s) %s\n",bcmos_strerror(ret),
                    pon_interface_set_state.hdr.hdr.err_text);
            sem_destroy(&interface_cb_mutex);
            break;
        }
        else
        {
            printf("interface activation operation success\n");
#ifndef BCMOLT_API_STUB

            /* Wait for the interface activation to successfully complete */
            printf("waiting for interface activation complete indication...\n");
            sem_wait(&interface_cb_mutex);

#endif /* BCMOLT_API_STUB */

            printf("interface activation complete\n");
            sem_destroy(&interface_cb_mutex);
        }

        /* Configure ONU 2 on PON 0 */
        {
            bcmolt_onu_cfg cfg;
            bcmolt_onu_key key = {.pon_ni = 0, .onu_id = 2};
            bcmolt_serial_number serial_number =
                {.vendor_id.arr = {0x42,0x52,0x43, 0x4D}, .vendor_specific.arr = {0x23,0x45,0x67, 0x89}};

            BCMOLT_CFG_INIT(&cfg, onu, key);
            BCMOLT_MSG_FIELD_SET(&cfg, itu.serial_number, serial_number);
            BCMOLT_MSG_FIELD_SET(&cfg, itu.auto_learning, BCMOS_TRUE);

            /*set burst and data profiles to fec disabled*/
            BCMOLT_MSG_FIELD_SET(&cfg, itu.xgpon.ranging_burst_profile, 0);
            BCMOLT_MSG_FIELD_SET(&cfg, itu.xgpon.data_burst_profile, 1);

            ret = bcmolt_cfg_set(0, &cfg.hdr);
            if(BCM_ERR_OK != ret)
            {
                fprintf(stderr, "error detected trying to configure an onu (%s)\n",bcmos_strerror(ret));
                break;
            }
            else
            {
                printf("onu configured\n");
            }
        }

        /* Configure SP TM_SCHED and an associated TM_QUEUE on PON 0 */
        {
            bcmolt_tm_sched_cfg tm_sched_cfg;
            bcmolt_tm_sched_key tm_sched_key = {};

            bcmolt_tm_queue_key tm_queue_key = {};
            bcmolt_tm_queue_cfg tm_queue_cfg;

            /* tm_sched */
            tm_sched_key.id = 1;
            BCMOLT_CFG_INIT(&tm_sched_cfg, tm_sched, tm_sched_key);

            BCMOLT_MSG_FIELD_SET(&tm_sched_cfg, attachment_point.type, BCMOLT_TM_SCHED_OUTPUT_TYPE_INTERFACE);
            BCMOLT_MSG_FIELD_SET(&tm_sched_cfg, attachment_point.u.interface.interface_ref.intf_type, BCMOLT_INTERFACE_TYPE_PON);
            BCMOLT_MSG_FIELD_SET(&tm_sched_cfg, attachment_point.u.interface.interface_ref.intf_id, 0);

            BCMOLT_MSG_FIELD_SET(&tm_sched_cfg, sched_type, BCMOLT_TM_SCHED_TYPE_SP);
            BCMOLT_MSG_FIELD_SET(&tm_sched_cfg, num_priorities, 4);

            ret = bcmolt_cfg_set(0, &tm_sched_cfg.hdr);
            if(BCM_ERR_OK != ret)
            {
                fprintf(stderr, "error detected trying to configure a tm_sched (%s)\n",bcmos_strerror(ret));
                break;
            }
            else
            {
                printf("tm_sched configured\n");
            }

            /* tm_queue */
            tm_queue_key.sched_id = 1;
            tm_queue_key.id = 1;
            tm_queue_key.tm_q_set_id = BCMOLT_TM_QUEUE_SET_ID_QSET_NOT_USE;
            BCMOLT_CFG_INIT(&tm_queue_cfg, tm_queue, tm_queue_key);
            BCMOLT_MSG_FIELD_SET(&tm_queue_cfg, tm_sched_param.type, BCMOLT_TM_SCHED_PARAM_TYPE_PRIORITY);
            BCMOLT_MSG_FIELD_SET(&tm_queue_cfg, tm_sched_param.u.priority.priority, 1);
            ret = bcmolt_cfg_set(0, &tm_queue_cfg.hdr);
            if(BCM_ERR_OK != ret)
            {
                fprintf(stderr, "error detected trying to configure a tm_queue (%s)\n",bcmos_strerror(ret));
                break;
            }
            else
            {
                printf("tm_queue configured\n");
            }
        }

        /* Configure a DS FLOW on PON 0/ONU 2, using TM_SCHED and TM_QUEUE above */
        {
            bcmolt_flow_key flow_key = {.flow_id = 1, .flow_type = BCMOLT_FLOW_TYPE_DOWNSTREAM};
            bcmolt_flow_cfg flow_cfg;

            BCMOLT_CFG_INIT(&flow_cfg, flow, flow_key);

            /* FROM NNI 0 */
            BCMOLT_MSG_FIELD_SET(&flow_cfg, ingress_intf.intf_type, BCMOLT_INTERFACE_TYPE_NNI);
            BCMOLT_MSG_FIELD_SET(&flow_cfg, ingress_intf.intf_id, 0);

            /* TO PON 0 */
            BCMOLT_MSG_FIELD_SET(&flow_cfg, egress_intf.intf_type, BCMOLT_INTERFACE_TYPE_PON);
            BCMOLT_MSG_FIELD_SET(&flow_cfg, egress_intf.intf_id, 0);

            /* SINGLE TAG - VID 100 */
            BCMOLT_MSG_FIELD_SET(&flow_cfg, classifier. pkt_tag_type, BCMOLT_PKT_TAG_TYPE_SINGLE_TAG);
            BCMOLT_MSG_FIELD_SET(&flow_cfg, classifier.o_vid, 100);

            /* ATTACH TO TM_SCHED 1 */
            BCMOLT_MSG_FIELD_SET(&flow_cfg , egress_qos.type, BCMOLT_EGRESS_QOS_TYPE_FIXED_QUEUE);
            BCMOLT_MSG_FIELD_SET(&flow_cfg , egress_qos.tm_sched.id, 1);

            /* USING TM_QUEUE 1 */
            BCMOLT_MSG_FIELD_SET(&flow_cfg , egress_qos.u.fixed_queue.queue_id, 1);

            /* FOR ONU 2 */
            BCMOLT_MSG_FIELD_SET(&flow_cfg , onu_id, 2);

            /* Let the system choose a GEM */
            BCMOLT_MSG_FIELD_SET(&flow_cfg , svc_port_id, BCMOLT_SERVICE_PORT_ID_NEXT_FREE);

            /* And enable the flow */
            BCMOLT_MSG_FIELD_SET(&flow_cfg, state, BCMOLT_FLOW_STATE_ENABLE);

            ret = bcmolt_cfg_set(0, &flow_cfg.hdr);
            if(BCM_ERR_OK != ret)
            {
                fprintf(stderr, "error detected trying to configure a flow (%s)\n",bcmos_strerror(ret));
                break;
            }
            else
            {
                printf("flow configured\n");
            }
        }

    } while(BCMOS_FALSE);

    return ret;
}

static void user_appl_indication_cb(bcmolt_devid olt, bcmolt_msg *msg)
{
    switch(msg->obj_type)
    {
        case BCMOLT_OBJ_ID_DEVICE:
        {
            printf("[-- olt %u: Device Indication Received --]\n", olt);
            switch(msg->subgroup)
            {
                case BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_FAILURE:
                    break;

                case BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_COMPLETE:
                {
                    bcmolt_device_connection_complete *ind = (bcmolt_device_connection_complete *)msg;

                    printf("olt %u: device id [%d] connection is complete"
#ifndef BCMOLT_API_STUB
                        ", system_mode is %s, standalone=%d"
#endif
                        "\n",
                           olt
                           ,ind->key.device_id
#ifndef BCMOLT_API_STUB
                           ,bcmolt_enum_stringval(bcmolt_system_mode_string_table, ind->data.system_mode)
                           ,ind->data.standalone
#endif
                           );

                    sem_post(&connect_cb_mutex);
                    break;
                }
                default:
                    fprintf(stderr, "unexpected device indication received\n");
                    break;
            }
            break;
        }
        case BCMOLT_OBJ_ID_PON_INTERFACE:
        {
            bcmolt_pon_interface_state_change_completed *pon_intf_ind =
                (bcmolt_pon_interface_state_change_completed *)msg;

            printf("[-- olt %u: Pon Interface Indication Received for pon %u --]\n", olt, pon_intf_ind->key.pon_ni);
            switch(msg->subgroup)
            {
                case BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_STATE_CHANGE_COMPLETED:
                    printf("pon interface state change indication %s\n",
                           pon_intf_ind->data.result ? "failed" : "success");
                    if (!pon_intf_ind->data.result)
                    {
                        printf("pon interface has changed state from %s to %s\n",
                               bcmolt_enum_stringval(bcmolt_interface_state_string_table,
                                                     pon_intf_ind->data.previous_state),
                               bcmolt_enum_stringval(bcmolt_interface_state_string_table,
                                                     pon_intf_ind->data.new_state));
                   }
                    sem_post(&interface_cb_mutex);
                    break;
                default:
                    fprintf(stderr, "unexpected interface indication received\n");
                    break;
            }
            break;
        }
        default:
        {
            fprintf(stderr, "unexpected object indication received (%s)\n",
                   bcmolt_enum_stringval(bcmolt_obj_id_string_table, msg->obj_type));
            break;
        }
    }
    bcmolt_msg_free(msg);
}
