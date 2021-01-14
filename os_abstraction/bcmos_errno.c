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
#include "bcmos_system.h"

/* Map error code to error string */
const char *bcmos_strerror(bcmos_errno err)
{
    static const char *errstr[] = {
        [-BCM_ERR_OK]                        = "OK",
        [-BCM_ERR_IN_PROGRESS]               = "In progress",
        [-BCM_ERR_PARM]                      = "Error in parameters",
        [-BCM_ERR_NOMEM]                     = "No memory",
        [-BCM_ERR_NORES]                     = "No resources",
        [-BCM_ERR_INTERNAL]                  = "Internal error",
        [-BCM_ERR_NOENT]                     = "Entry doesn't exist",
        [-BCM_ERR_NODEV]                     = "Device doesn't exist",
        [-BCM_ERR_ALREADY]                   = "Entry already exists/already in requested state",
        [-BCM_ERR_RANGE]                     = "Out of range",
        [-BCM_ERR_PERM]                      = "No permission to perform an operation",
        [-BCM_ERR_NOT_SUPPORTED]             = "Operation is not supported",
        [-BCM_ERR_PARSE]                     = "Parsing error",
        [-BCM_ERR_INVALID_OP]                = "Invalid operation",
        [-BCM_ERR_IO]                        = "I/O error",
        [-BCM_ERR_STATE]                     = "Object is in bad state",
        [-BCM_ERR_DELETED]                   = "Object is deleted",
        [-BCM_ERR_TOO_MANY]                  = "Too many objects",
        [-BCM_ERR_NO_MORE]                   = "No more entries",
        [-BCM_ERR_OVERFLOW]                  = "Buffer overflow",
        [-BCM_ERR_COMM_FAIL]                 = "Communication failure",
        [-BCM_ERR_NOT_CONNECTED]             = "No connection with the target system",
        [-BCM_ERR_SYSCALL_ERR]               = "System call returned error",
        [-BCM_ERR_MSG_ERROR]                 = "Received message is insane",
        [-BCM_ERR_TOO_MANY_REQS]             = "Too many outstanding requests",
        [-BCM_ERR_TIMEOUT]                   = "Operation timed out",
        [-BCM_ERR_TOO_MANY_FRAGS]            = "Too many fragments",
        [-BCM_ERR_NULL]                      = "Got NULL pointer",
        [-BCM_ERR_READ_ONLY]                 = "Attempt to set read-only parameter",
        [-BCM_ERR_ONU_ERR_RESP]              = "ONU returned an error response",
        [-BCM_ERR_MANDATORY_PARM_IS_MISSING] = "Mandatory parameter is missing",
        [-BCM_ERR_KEY_RANGE]                 = "Key field out of range",
        [-BCM_ERR_QUEUE_EMPTY]               = "Rx of PCIe empty",
        [-BCM_ERR_QUEUE_FULL]                = "Tx of PCIe full",
        [-BCM_ERR_TOO_LONG]                  = "Processing is taking too long, but will finish eventually",
        [-BCM_ERR_INSUFFICIENT_LIST_MEM]     = "Insufficient list memory provided",
        [-BCM_ERR_OUT_OF_SYNC]               = "Sequence number or operation step was out of sync",
        [-BCM_ERR_CHECKSUM]                  = "Checksum error",
        [-BCM_ERR_IMAGE_TYPE]                = "Unsupported file/image type",
        [-BCM_ERR_INCOMPLETE_TERMINATION]    = "Incomplete premature termination",
        [-BCM_ERR_MISMATCH]                  = "Parameters mismatch",
    };
    static const char *unknown = "*unknown*";

    if ((unsigned)(-err) >= sizeof(errstr)/sizeof(errstr[0]) || !errstr[-err])
        return unknown;
    return errstr[-err];
}

#ifdef __KERNEL__
EXPORT_SYMBOL(bcmos_strerror);
#endif
