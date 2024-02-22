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


#include <sys/socket.h>
#include <sys/un.h>

#include <bcmos_system.h>
#include <bcmtr_header.h>
#include <bcmtr_plugin.h>
#include <bcm_config.h>
#include <bcmtr_plugin_unix_domain.h>
#include <bcmolt_msg.h>
#include <bcmolt_math.h>  /* MAX, MIN */

/* #define UD_PLUGIN_DEBUG */
#ifdef UD_PLUGIN_DEBUG
#define UD_PLUGIN_PRINT(_fmt, ...) bcmos_printf("%s#%d: " _fmt, __FUNCTION__, __LINE__, ## __VA_ARGS__)
#else
#define UD_PLUGIN_PRINT(_fmt, ...)
#endif

/* Plugin channel structure */
static struct
{
    int sock;                   /* UD socket */
    uint64_t device_mask;
    bcmos_task rx_task;
    bcmtr_plugin_recv_info recv_info;
    bcmos_mutex lock;
} bcmtr_ud_data;
#define DEVICE_MASK(device)     (1LL << device)

/*
#define DEBUG_TRACE 1
*/

/* This plugin stores both device id and per-device socket handle in
 * transport's channel_id handle as
 * (device_id << 24) | socket_handle.
 * The following functions recover socket_handle and device_id from the channel_id handle
 */

/** Close socket */
static void bcmtr_ud_socket_close(void)
{
    UD_PLUGIN_PRINT("Disconnected from device management daemon\n");
    bcmos_mutex_lock(&bcmtr_ud_data.lock);
    if (bcmtr_ud_data.sock > 0)
    {
        close(bcmtr_ud_data.sock);
        bcmtr_ud_data.sock = -1;
    }
    bcmos_mutex_unlock(&bcmtr_ud_data.lock);
}

/** Open socket */
static bcmos_errno bcmtr_ud_socket_open(void)
{
    struct sockaddr_un addr;
    int sock;
    bcmos_errno err;

    bcmos_mutex_lock(&bcmtr_ud_data.lock);
    do
    {
        if (bcmtr_ud_data.sock > 0)
        {
            err = BCM_ERR_OK;
            break;
        }

        if ( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
        {
            bcmos_printf("Couldn't create Unix Domain socket. Error %s\n", strerror(errno));
            err = BCM_ERR_IO;
            break;
        }

        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        snprintf(addr.sun_path, sizeof(addr.sun_path), "%s_%s", SOCKET_PATH, getenv("USER"));
        /*  First char NULL --> make this an anonymous socket without file system entries to clean up */
        addr.sun_path[0]=0;
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
        {
            close(sock);
            err = BCM_ERR_IO;
            break;
        }
        err = BCM_ERR_OK;
        bcmtr_ud_data.sock = sock;
        UD_PLUGIN_PRINT("Connected to device management daemon\n");
    } while (0);
    bcmos_mutex_unlock(&bcmtr_ud_data.lock);

    return err;
}

/** Send data */
static bcmos_errno bcmtr_ud_send(
    bcmtr_plugin_channel ch,
    bcmolt_devid device,
    bcmolt_subchannel subch,
    bcmos_buf *buf,
    bcmtr_send_flags flags)
{
    int buflen = bcmos_buf_length(buf);
    uint8_t *p_hdr_buf = bcmos_buf_head_push(buf, sizeof(bcmud_packet_hdr));
    bcmud_packet_hdr hdr;
    int total_len = buflen + sizeof(bcmud_packet_hdr);
    int len;

    /* Return if not connected (a race condition) */
    if (bcmtr_ud_data.sock == -1)
    {
        bcmos_buf_free(buf);
        return BCM_ERR_NOT_CONNECTED;
    }

    hdr.data_length = buflen;
    hdr.device = device;
    memcpy(p_hdr_buf, &hdr, sizeof(hdr));
    len = send(bcmtr_ud_data.sock, p_hdr_buf, total_len, 0);

    /* Buffer is no longer needed */
    bcmos_buf_free(buf);

    if (len < total_len)
    {
        UD_PLUGIN_PRINT("%s: sock_sendmsg(%u) --> %d. errno=%d\n", __FUNCTION__, buflen, len, errno);
        bcmtr_ud_socket_close();
        return BCM_ERR_COMM_FAIL;
    }

    return BCM_ERR_OK;
}

/** Receive data */
static bcmos_errno bcmtr_ud_recv(bcmtr_plugin_channel ch, bcmolt_devid *device, bcmolt_subchannel *subch, bcmos_buf **pbuf)
{
    bcmud_packet_hdr hdr;
    bcmos_buf *buf;
    int len;
    fd_set read_fds;
    struct timeval tv;
    int rc;

    /* Return if not connected (a race condition) */
    if (bcmtr_ud_data.sock == -1)
    {
        return BCM_ERR_NOT_CONNECTED;
    }

    BUG_ON(bcmtr_ud_data.sock < 0);
    FD_ZERO(&read_fds);
    FD_SET(bcmtr_ud_data.sock, &read_fds);
    tv.tv_sec = (BCMTR_MSG_TIMEOUT * 1000) / 1000000;
    tv.tv_usec = (BCMTR_MSG_TIMEOUT * 1000) % 1000000;

    rc = select(bcmtr_ud_data.sock + 1, &read_fds, NULL, NULL, &tv);
    if (rc < 0)
    {
        UD_PLUGIN_PRINT("Select failed. Error %s\n", strerror(errno));
        return BCM_ERR_IO;
    }
    if (!rc || !FD_ISSET(bcmtr_ud_data.sock, &read_fds))
    {
        return BCM_ERR_TIMEOUT;
    }

    /* Read plugin header first */
    len = recv(bcmtr_ud_data.sock, &hdr, sizeof(hdr), 0);
    if (len < sizeof(hdr))
    {
        UD_PLUGIN_PRINT("%s: Received len %d < %u\n", __FUNCTION__, len, sizeof(hdr));
        bcmtr_ud_socket_close();
        return BCM_ERR_COMM_FAIL;
    }

    /* Make sure that header is sane */
    if (hdr.data_length > BCMTR_MAX_MTU_SIZE)
    {
        UD_PLUGIN_PRINT("Received UD plugin header is insane. data_length=%u > MAX_MTU_SIZE=%u\n",
            hdr.data_length, BCMTR_MAX_MTU_SIZE);
        bcmtr_ud_socket_close();
        return BCM_ERR_COMM_FAIL;
    }

    /* Allocate buffer and receive the UD plugin header and actual data */
    buf = bcmos_buf_alloc(hdr.data_length);
    if (buf == NULL)
    {
        UD_PLUGIN_PRINT("Can't allocate buffer\n");
        bcmtr_ud_socket_close();
        return BCM_ERR_NOMEM;
    }

    /* Read data */
    len = recv(bcmtr_ud_data.sock, bcmos_buf_data(buf), hdr.data_length, 0);
    if (len < hdr.data_length)
    {
        UD_PLUGIN_PRINT("Received data is too short. Expected %u bytes, received %d\n",
            hdr.data_length, len);
        bcmos_buf_free(buf);
        bcmtr_ud_socket_close();
        return BCM_ERR_COMM_FAIL;
    }

    bcmos_buf_length_set(buf, len);
    *device = (bcmolt_devid)hdr.device;
    *pbuf = buf;
    *subch = 0;

    return BCM_ERR_OK;
}

/** Open communication channel */
static bcmos_errno bcmtr_ud_open(bcmolt_devid device, bcmtr_plugin_cfg *cfg, bcmtr_plugin_channel *ch)
{
    bcmos_errno err;

    if ((bcmtr_ud_data.device_mask & DEVICE_MASK(device)) != 0)
        return BCM_ERR_ALREADY;

    if (!bcmtr_ud_data.device_mask)
    {
        err = bcmtr_ud_socket_open();
        if (err != BCM_ERR_OK)
            return err;
        /* Create transport RX task */
        bcmtr_ud_data.recv_info.ch = (bcmtr_plugin_channel)&bcmtr_ud_data;
        bcmtr_ud_data.recv_info.recv = bcmtr_ud_recv;
        err = bcmtr_rx_task_create(&bcmtr_ud_data.rx_task, "tr_rx_ud", &bcmtr_ud_data.recv_info);
        if (err != BCM_ERR_OK)
        {
            bcmtr_ud_socket_close();
            BCMOS_TRACE_RETURN(err, "Failed to create transport RX task\n");
        }
    }
    bcmtr_ud_data.device_mask |= DEVICE_MASK(device);
    *ch = (bcmtr_plugin_channel)device;

    return BCM_ERR_OK;
}

/** Close communication channel */
static bcmos_errno bcmtr_ud_close(bcmtr_plugin_channel ch)
{
    bcmolt_devid device = (bcmolt_devid)ch;
    if ((bcmtr_ud_data.device_mask & DEVICE_MASK(device)) == 0)
        return BCM_ERR_ALREADY;
    bcmtr_ud_data.device_mask &= ~DEVICE_MASK(device);
    if (!bcmtr_ud_data.device_mask)
    {
        bcmos_task_destroy(&bcmtr_ud_data.rx_task);
        bcmtr_ud_socket_close();
    }
    return BCM_ERR_OK;
}

/** Initialize plugin callbacks
 * \param[in,out]       driver Transport plugin driver structure
 * \return error code
 */
bcmos_errno bcmtr_plugin_unix_domain_init(bcmtr_plugin_cfg *cfg, bcmtr_driver *driver)
{
    static bcmos_bool first_call = BCMOS_TRUE;
    if (first_call)
    {
        bcmos_printf("Launching with a unix domain connection\n");
        first_call = BCMOS_FALSE;
        bcmos_mutex_create(&bcmtr_ud_data.lock, 0, "tr_ud");
    }

    driver->open = bcmtr_ud_open;
    driver->close = bcmtr_ud_close;
    driver->send = bcmtr_ud_send;

    return BCM_ERR_OK;
}
