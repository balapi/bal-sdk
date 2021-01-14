/*
<:copyright-BRCM:2018-2020:Apache:standard

 Copyright (c) 2018-2020 Broadcom. All Rights Reserved

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
#ifndef BCMOLT_API_WRITER_H_
#define BCMOLT_API_WRITER_H_

/* bcmolt_api_writer.h
 * Utility functions to write the contents of a message/structure/field to an output stream in a readable format.
 */

#include <bcmos_system.h>
#include <bcmolt_msg.h>
#include <bcmolt_metadata_writer.h>

/* Write full API message. */
bcmos_errno bcmolt_api_write_msg(const bcmolt_metadata_writer *writer, const bcmolt_msg *msg, uint32_t style);

#endif /* BCMOLT_API_WRITER_H_ */
