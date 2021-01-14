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

/* bcmolt_conn_mgr_udp_socket.c - connection manager: UDP transport using posix socket.
 */

#include <bcmolt_conn_mgr_internal.h>
#include <bcm_dev_log.h>

typedef struct cmll_udp_info
{
    int sock;
    fd_set read_fds;
    void *drv_data;
} cmll_udp_info;
static cmll_udp_info cmll_info[BCMOLT_CONN_TYPE__NUM_OF];
static cmll_udp_info *cmll_info_ptrs[BCMOLT_CONN_TYPE__NUM_OF];
static uint32_t cmll_max_mtu;

/* Send to peer */
static bcmos_errno _cmll_udp_send(bcmolt_cmll_conn_id ll_conn_id, bcmos_buf *buf, const bcmolt_cm_addr *addr)
{
    struct sockaddr_in peer_addr =
    {
        .sin_family = AF_INET,
        .sin_port = htons(addr->udp.port),
        .sin_addr.s_addr = htonl(addr->udp.ip.u32)
    };
    uint32_t buflen = bcmos_buf_length(buf);
    struct iovec iov =
    {
        .iov_base = bcmos_buf_data(buf),
        .iov_len = buflen
    };
    struct msghdr msg =
    {
        .msg_iov = &iov, .msg_iovlen = 1,
        .msg_name = (void *)&peer_addr, .msg_namelen = sizeof(peer_addr)
    };
    int len;

    len = sendmsg((int)ll_conn_id, &msg, 0);
    bcmos_buf_free(buf);

    return (len < (long)buflen) ? BCM_ERR_COMM_FAIL : BCM_ERR_OK;
}

/* Check for new RX packet. Called from receive task if CMLL_INIT_FLAG_CREATE_RX_TASK flag is set */
static bcmos_errno _cmll_udp_check_recv(long ll_handle, bcmolt_cmll_conn_id *ll_conn_id,
    bcmos_buf *buf, bcmolt_cm_addr *addr, bcmolt_cm_conn_id *conn_id)
{
    cmll_udp_info *info_ptr = (cmll_udp_info *)ll_handle;
    struct sockaddr_in peer_addr;
    struct iovec iov =
    {
        .iov_base = bcmos_buf_data(buf),
        .iov_len = cmll_max_mtu
    };
    struct msghdr msg =
    {
        .msg_iov = &iov, .msg_iovlen = 1,
        .msg_name = (void *)&peer_addr, .msg_namelen = sizeof(peer_addr)
    };
    int len;
    fd_set read_fds;
    struct timeval tv;
    int rc;

    read_fds = info_ptr->read_fds;

    tv.tv_sec = (BCMTR_MSG_TIMEOUT * 1000) / 1000000;
    tv.tv_usec = (BCMTR_MSG_TIMEOUT * 1000) % 1000000;

    rc = select(info_ptr->sock + 1, &read_fds, NULL, NULL, &tv);
    if (rc < 0)
        return BCM_ERR_IO;

    if (!rc)
        return BCM_ERR_TIMEOUT;

    len = recvmsg(info_ptr->sock, &msg, 0);
    if (len <= 0)
        return BCM_ERR_COMM_FAIL;

    /* Received packet */
    bcmos_buf_length_set(buf, len);
    addr->udp.port = ntohs(peer_addr.sin_port);
    addr->udp.ip.u32 = ntohl(peer_addr.sin_addr.s_addr);
    *ll_conn_id = info_ptr->sock;

    return BCM_ERR_OK;
}

/* Initialize underlying transport for specific connection type */
static bcmos_errno _cmll_udp_init1(cmll_udp_info *info_ptr, const bcmolt_cm_addr *addr)
{
    /* Create UDP socket. A single socket is shared by all connections */
    struct sockaddr_in my_addr = {};
    struct timeval timeout = { .tv_sec = BCMTR_MSG_TIMEOUT/1000, .tv_usec = (BCMTR_MSG_TIMEOUT % 1000) * 1000 };
    int mtu_discover;

    info_ptr->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (info_ptr->sock < 0)
    {
        CM_LOG_ERR_RETURN(BCM_ERR_COMM_FAIL, "Can't create UDP socket\n");
    }

    /* Bind local */
    if (addr != NULL && addr->udp.port)
    {
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(addr->udp.port);
        my_addr.sin_addr.s_addr = htonl(addr->udp.ip.u32);
        if (bind(info_ptr->sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
        {
            close(info_ptr->sock);
            info_ptr->sock = -1;
            CM_LOG_ERR_RETURN(BCM_ERR_COMM_FAIL, "Can't bind UDP socket to %d.%d.%d.%d:%d\n",
                (int)addr->udp.ip.u8[0], (int)addr->udp.ip.u8[1], (int)addr->udp.ip.u8[2], (int)addr->udp.ip.u8[3],
                (int)addr->udp.port);
        }
        CM_LOG(INFO, "IB transport: UDP socket bound to port %d\n", (int)addr->udp.port);
    }

    if (setsockopt(info_ptr->sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        close(info_ptr->sock);
        info_ptr->sock = -1;
        CM_LOG_ERR_RETURN(BCM_ERR_COMM_FAIL, "Can't set socket option for send timeout\n");
    }

    /* Always use the DF flag to disable IP fragmentation */
    mtu_discover = IP_PMTUDISC_DO;
    if (setsockopt(info_ptr->sock, IPPROTO_IP, IP_MTU_DISCOVER, &mtu_discover, sizeof(mtu_discover)) < 0)
    {
        close(info_ptr->sock);
        info_ptr->sock = -1;
        CM_LOG_ERR_RETURN(BCM_ERR_COMM_FAIL, "Can't set socket option for DF\n");
    }

    FD_ZERO(&info_ptr->read_fds);
    FD_SET(info_ptr->sock, &info_ptr->read_fds);

    return BCM_ERR_OK;
}

/* Connect */
static bcmos_errno _cmll_udp_connect(long ll_handle, bcmolt_conn_type conn_type, bcmolt_subchannel conn_id,
    const bcmolt_cm_addr *addr, bcmolt_cmll_conn_id *ll_conn_id)
{
    cmll_udp_info *info_ptr = (cmll_udp_info *)ll_handle;
    if (info_ptr == NULL || info_ptr->sock < 0)
        return BCM_ERR_INTERNAL;
    *ll_conn_id = info_ptr->sock;
    return BCM_ERR_OK;
}

/* Disable connection types */
static void _cmll_udp_disable(long ll_handle)
{
    cmll_udp_info *info_ptr = (cmll_udp_info *)ll_handle;
    int conn_type;

    if (info_ptr == NULL)
        return;

    for (conn_type = 0; conn_type < (int)BCMOLT_CONN_TYPE__NUM_OF; conn_type++)
    {
        if (info_ptr == cmll_info_ptrs[conn_type])
            cmll_info_ptrs[conn_type] = NULL;
    }
    if (info_ptr->sock >= 0)
    {
        close(info_ptr->sock);
        info_ptr->sock = -1;
    }
}

/* Enable connection types */
static bcmos_errno _cmll_udp_enable(bcmolt_conn_type_mask conn_types, const bcmolt_cm_addr *local_addr,
    void *drv_data, long *ll_handle)
{
    cmll_udp_info *info_ptr = NULL;
    int conn_type;
    bcmos_errno err = BCM_ERR_OK;

    for (conn_type = 0; conn_type < (int)BCMOLT_CONN_TYPE__NUM_OF; conn_type++)
    {
        if ((conn_types & BCMOLT_CONN_TYPE_MASK(conn_type)) != 0)
        {
            if (info_ptr == NULL)
                info_ptr = &cmll_info[conn_type];
            cmll_info_ptrs[conn_type] = info_ptr;
        }
    }
    BUG_ON(info_ptr == NULL);
    info_ptr->sock = -1;
    err = _cmll_udp_init1(info_ptr, local_addr);
    if (err != BCM_ERR_OK)
    {
        _cmll_udp_disable((long)info_ptr);
        return err;
    }

    info_ptr->drv_data = drv_data;
    *ll_handle = (long)info_ptr;

    return BCM_ERR_OK;
}

/* Compare addresses */
static bcmos_bool _cmll_udp_addr_is_equal(const bcmolt_cm_addr *addr1, const bcmolt_cm_addr *addr2)
{
    return (addr1->udp.ip.u32 == addr2->udp.ip.u32 && addr1->udp.port == addr2->udp.port);
}

/* Initialize underlying transport.
   Returns *init_flags
 */
bcmos_errno bcmolt_cmll_init(const bcmolt_cm_init_parms *init_parms, bcmolt_cmll_driver *driver)
{
    /* Init driver callbacks */
    driver->flags = CMLL_INIT_FLAG_CREATE_RX_TASK;
    driver->check_recv = _cmll_udp_check_recv;
    driver->send = _cmll_udp_send;
    driver->connect = _cmll_udp_connect;
    driver->enable = _cmll_udp_enable;
    driver->disable = _cmll_udp_disable;
    driver->addr_is_equal = _cmll_udp_addr_is_equal;

    cmll_max_mtu = init_parms->max_mtu;

    return BCM_ERR_OK;
}
