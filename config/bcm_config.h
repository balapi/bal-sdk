/*
<:copyright-BRCM:2016-2019:Apache:standard

 Copyright (c) 2016-2019 Broadcom. All Rights Reserved

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

 *  :>
 */

#ifndef BCMOLT_CONFIG_H_
#define BCMOLT_CONFIG_H_

/** \defgroup config Configuration Constants
 * Configuration constants that must be revised by customer
 * @{
 */

/** CPU Endianness. Must be set to BCMOS_ENDIAN_BIG or BCMOS_ENDIAN_LITTLE. */
#ifndef BCM_CPU_ENDIAN
#error BCM_CPU_ENDIAN must be set BCMOS_ENDIAN_BIG or BCMOS_ENDIAN_LITTLE
#endif /* #ifndef BCM_CPU_ENDIAN */

/** Broadcom MAC device type from bcm_mac_device_type.
 * If set BCM_MAC_DEVICE_TYPE_UNKNOWN, device type is identified automatically at run time
 */
#define BCM_MAC_DEVICE_TYPE   BCM_MAC_DEVICE_TYPE_UNKNOWN

/**
 * System topology configuration
 */

/** Max number of line cards controlled by API layer.
 * - if application is ON the line card, it controls only this line card and BCM_MAX_LINE_CARDS should be 1
 * - If application is remote, it can control multiple line cards. In this case BCM_MAX_LINE_CARDS can be >1
 */
#define BCM_MAX_LINE_CARDS          1

/** Max number of MAC devices per line card */
#define BCM_MAX_DEVS_PER_LINE_CARD  2

/** Max number of MAC devices per OLT
 * - Set =BCM_MAX_DEVS_PER_LINE_CARD for Full line card mode
 * - Set =1 for Maple backward compatibility mode
 * - Set to some other number for PON-level line card slicing
 */
#define BCM_MAX_DEVS_PER_OLT        BCM_MAX_DEVS_PER_LINE_CARD

/** Max number of MAC devices globally (on all controlled line cards) */
#define BCM_MAX_DEVS                (BCM_MAX_LINE_CARDS * BCM_MAX_DEVS_PER_LINE_CARD)

/** Max number of OLTs per line card
 * - Set =1 for full line card mode
 * - Set =BCM_MAX_DEVS_PER_LINE_CARD for Maple backward compatibility mode
 * - Set to some other number for PON-level line card slicing
 */
#define BCM_MAX_OLTS_PER_LINE_CARD  BCM_MAX_DEVS_PER_LINE_CARD

/** Max number of OLTs controlled by API layer.
 * An OLT can manage 0 or 1 switch device and 1 to BCM_MAX_DEVS_PER_OLT number of MAC devices.
 * - Full line card is mode is a single switch and 1 to BCM_MAX_DEVS_PER_OLT MAC devices.
 * - MAC only mode no switch and 1 to BCM_MAX_DEVS_PER_OLT MAC devices
 * - Maple backward compatibility mode is no switch and 1 MAC device.
 *   In this case there is an OLT object per MAC device
 */
#define BCM_MAX_OLTS                (BCM_MAX_LINE_CARDS * BCM_MAX_OLTS_PER_LINE_CARD)

/** Max number of PON interfaces per device */
#define BCM_MAX_PONS_PER_DEV        16

/** Max number of PON interfaces per line card */
#define BCM_MAX_PONS_PER_LINE_CARD  (BCM_MAX_DEVS_PER_LINE_CARD * BCM_MAX_PONS_PER_DEV)

/** Max number of PON interfaces per OLT */
#define BCM_MAX_PONS_PER_OLT        (BCM_MAX_DEVS_PER_OLT * BCM_MAX_PONS_PER_DEV)

/** Max number of applications that can communicate with transport MUX simultaneously */
#define BCM_MAX_CLIENTS             8

/** Max number of NNI interfaces configurable in Switch */
/** @note need to allow config of Inband ports (upto 4 ports typically)  after max network NNIs of 16 ports.
  * Since for Switch, Inband ports are considered as part of NNI ports (though not network facing),
  * the max define should accommodate that.
  * Also note, BAL software still allows only 16 NNI network facing ports to be configured.
  */
#define BCM_MAX_NNI_PER_OLT         (BCM_MAX_NETWORK_NNI_PER_OLT + BCM_MAX_NIC_NNI_PER_OLT)

/** Max number of network facing NNIs configurable in  Switch */
#define BCM_MAX_NETWORK_NNI_PER_OLT 16

/**  @note This defines the max physical NIC interfaces that might be available on the OLT. */
#define BCM_MAX_NIC_NNI_PER_OLT 4

/** Max number of Internal NNI interfaces per OLT */
#define BCM_MAX_INNI_PER_OLT        32

/** Max BAL startup time */
#define BCM_BAL_STARTUP_TIMEOUT     80000000 /* 80s */

/**
 * Transport layer configuration defaults.
 * Usually there is no need to modify any of those constants
 */

/** Transport layer configuration defaults */
/* ToDo: remove BCMTR_MAX_OLTS (currently it is being used by dev agent ut) */
#define BCMTR_MAX_OLTS             BCM_MAX_OLTS      /**< Max number of OLTs */

#define BCMTR_MSG_TIMEOUT          1000    /**< Max time to wait for response or next message part (ms) */
#define BCMTR_MAX_REQUESTS         64     /**< Max number of outstanding requests per application per OLT */
#define BCMTR_MAX_AUTOS            256    /**< Maximum number of simultaneous multi-part autonomous messages */
#define BCMTR_MAX_FRAGMENTS        1000   /**< Maximum number of fragments per message */
#define BCMTR_MSG_WAIT_MS          5      /**< length of time to wait on conn read */
#define BCMTR_MSG_READY_MS         50     /**< Time to wait for application to peak up response */
#define BCMTR_MAX_MTU_SIZE         1450   /**< max MTU size (must leave >50 bytes of room for L2+UDP+IP header) */
#define BCMTR_RX_THREAD_STACK      0      /**< Rx thread stack size. 0=system default */
#define BCMTR_TIMEOUT_THREAD_STACK 0      /**< Timeout thread stack size. 0=system default */
#define BCMTR_MAX_DEVICES          BCM_MAX_DEVS         /**< Max number of MAC devices supported by the transport layer */
#define BCMTR_MAX_INSTANCES        BCM_MAX_PONS_PER_DEV /**< Max number of message handler instances - typically a number of PON's */

/** UDP transport plugic: default configuration */
#define BCMTR_TR_TYPE              BCMTR_TYPE_UDP       /**< Default transport type: raw/udp */
#define BCMTR_TR_UDP_HOST_IP       0x7f000001
#define BCMTR_TR_UDP_OLT_IP        0x7f000001
#define BCMTR_TR_UDP_HOST_PORT     0x4000
#define BCMTR_TR_UDP_OLT_PORT      0x4010

/** Debug output configuration */
#define BCM_DBG_MAX_MSG_SIZE       128    /**< Max number of message bytes to include in message dump */

#define BCMTR_BUF_EXTRA_HEADROOM   64     /**< Extra headroom to reserve in system buffer */

#define BCMTR_PCIE_START_TIMEOUT   30000  /**< Application start timeout (ms) */
#define BCMTR_PCIE_CONNECT_TIMEOUT 15000  /**< Connect timeout (ms) */
/** @} */

#define BCMTR_MAX_RXQ_SIZE         256

#endif /* BCMOLT_CONFIG_H_ */
