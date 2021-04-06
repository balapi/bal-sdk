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

/*
 * bcmolt_olt_selector.c
 * Set / get current OLT for all CLI commands
 */
#include <bcmos_system.h>
#include <bcmolt_olt_selector.h>
#include <bcmolt_api_topology.h>

/* current olt */
static bcmolt_oltid current_olt;

/* olt change callback registration structure */
typedef struct olt_sel_subscriber olt_sel_subscriber;
struct olt_sel_subscriber
{
    F_current_olt_change_ind cb;     /* Subscriber's callback */
    STAILQ_ENTRY(olt_sel_subscriber) next;
};

static STAILQ_HEAD(olt_sel_subscriber_list, olt_sel_subscriber) subscriber_list;

/* Get/set the current olt CLI handler
 */
static bcmos_errno _dev_sel_olt_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    olt_sel_subscriber *subs;

    if (nparms)
    {
        bcmolt_oltid olt = (bcmolt_oltid)parm[0].value.number;
        bcmolt_loid loid;

        /* Make sure that new current OLT is valid */
        if (bcmolt_apitopo_goid_to_loid(olt, &loid) != BCM_ERR_OK)
        {
            bcmcli_session_print(session, "OLT %u is not mapped\n", (unsigned)olt);
            return BCM_ERR_NOENT;
        }

        /* Notify all subscribers.
         * Do not check if it changed here. Sometimes it is good to be able to refresh.
         */
        current_olt = olt;

        /* Notify all subscribers */
        STAILQ_FOREACH(subs, &subscriber_list, next)
        {
            subs->cb(session, current_olt);
        }
    }

    bcmcli_session_print(session, "Current olt: %ld\n", (long)current_olt);

    return BCM_ERR_OK;
}


/* Register for current olt change notification.
 * Multiple clients can register.
 */
bcmos_errno bcmolt_olt_sel_ind_register(F_current_olt_change_ind cb)
{
    olt_sel_subscriber *subs = bcmos_calloc(sizeof(olt_sel_subscriber));

    if (!subs)
        return BCM_ERR_NOMEM;

    subs->cb = cb;
    STAILQ_INSERT_TAIL(&subscriber_list, subs, next);

    return BCM_ERR_OK;
}

/* Initialize olt selector module */
bcmos_errno bcmolt_olt_sel_init(bcmcli_entry *parent_dir)
{
    STAILQ_INIT(&subscriber_list);

    /* Get/set current olt */
    BCMCLI_MAKE_CMD(parent_dir, "olt", "Get/Set the current OLT", _dev_sel_olt_handler,
        BCMCLI_MAKE_PARM_RANGE("olt", "OLT index", BCMCLI_PARM_NUMBER, BCMCLI_PARM_FLAG_OPTIONAL,
            0, BCM_MAX_OLTS-1));

    return BCM_ERR_OK;
}

/* Get current olt */
bcmolt_oltid bcmolt_olt_sel_current(void)
{
    return current_olt;
}

