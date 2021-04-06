#  <:copyright-BRCM:2018-2020:Apache:standard
#
#   Copyright (c) 2018-2020 Broadcom. All Rights Reserved
#
#   The term “Broadcom” refers to Broadcom Inc. and/or its subsidiaries
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#  :>
#
#############################################################################/

#
# This is a raw make version of application integration with BAL API.
# To use this version libbal_host_api-oss.so must be built first by running 'make'
# in the root of BAL API source tree.
# hello_bal_app is dynamically linked with libbal_host_api-oss.so
#
BAL_API_BUILD_DIR ?= ../fs
BAL_API_LIB := bal_host_api-oss
BAL_API_INCLUDE_DIR := $(BAL_API_BUILD_DIR)/include

ifeq (,$(wildcard $(BAL_API_BUILD_DIR)/lib$(BAL_API_LIB).so))
    $(error "Please build lib$(BAL_API_LIB).so first by running 'make' in the root of the BAL API source tree")
endif

all: hello_bal_app

# This assumes a x86 host CPU
export BAL_EXTRA_CFLAGS = -lpthread -lrt -g -DBCMOS_MSG_QUEUE_DOMAIN_SOCKET -DSIMULATION_BUILD -pthread

# Build hello_bal with actual host API functions for real host API calls
hello_bal_app: hello_bal.c ../$(BAL_SO_LIB_NAME)
	gcc $(BAL_EXTRA_CFLAGS) hello_bal.c -L$(BAL_API_BUILD_DIR) -l$(BAL_API_LIB) -I $(BAL_API_INCLUDE_DIR) -o hello_bal_app

clean:
	rm -rf hello_bal_app
