
# BAL API SDK R3.10.4.4

## Overview
This repo supplies source and header files for building an Open Source version of BAL API
static and dynamic libraries.
The repo also includes an simple example code demonstrating how to use the BAL API.

Application built by the method #1 (hello_bal_app_static) or method #2 (hello_bal_app) can communicate with dev_mgmt_daemon
running on the line card.

             ---------------------
             |                   |
             |  hello_bal_app    |
             |                   |
             ---------------------                ----------------------------
             |                   |                |                          |
             |  libbal_host_api  |----------------|      dev_mgmt_daemon     |
             |                   |                |                          |
             ---------------------                ----------------------------
                                                  |  switch SDK | MAC SDK    |
                                                  ----------------------------
                                                  |  switch HW  |  MAC HW    |
                                                  ----------------------------

## Building the BAL API SDK and Appliction Example

### Prerequisites

* cmake version 3.5 or later
* make
* gcc compiler

The BAL API SDK is released with a built-in support for building on a linux PC using gcc toolchain.
Adding additional toolchains is discussed later in this document.

### Building BAL API SDK

*\> make [additional build parameters]*

The following additional build parameters can be specified after the 'make' command:
* BUILD_TOP_DIR=build-directory. The default build-directory is 'build'.
* V=1 - verbose build
* BOARD=board-name - build for the specified board. This option is explained later in this document.

#### BAL API SDK Build Artifacts

All build artifacts are created in directory build-directory/fs. The default build directory is 'build'.
* fs/libbal_host_api.so - shared library for BAL API applications that use dynamic linking
* fs/include - directory containing all BAL API header files

### Building BAL API application example

The included example demonstrates how to build a BAL API application in 2 different ways:

1. direct integration with BAL API SDK build system.
* application directory ('examples') is added to the BAL API SDK source tree
* reference to the application directory is added in the main CMakeLists.txt (bcm_add_subdirectory(examples))
* application directory must include CMakeLists.txt. See examples/CMakeLists.txt for reference

Application is built as part of the BAL API SDK build and is statically linked.
This method guarantees that application will use the same toolchain and compiler options as BAL API SDK.
No additional steps are required after building BAL API SDK.

2. separate build using a raw Makefile.
* BAL API SDK must be built first by running 'make' command in the root of the BAL API SDK source tree. It will create the following artifacts:
  * build/fs/libbal_host_api.so - BAL API shared library
  * build/fs/include - directory containing all BAL API header files
* Build the application using the header files and the shared library built in the previous step.

*\>cd build/example; make*

It is the responsibility of the user to ensure that toolchain and compilation options are correct.

### Running BAL API application example

BAL API application example invokes BAL APIs on a linecard running dev_mgmt_daemon.
Application built for linux PC always communicates with the linecard via UDP IP.

1. Start BAL dev_mgmt_daemon executable as per the procedure explained in the BAL Programmer's Guide.
2. Execute the example application:

*\>LD_LIBRARY_PATH=build/fs build/examples/hello_bal_app -transport UDP line-card-IP-address:50200*

It is also possible to build the application that will run directly on the line card.
Application built in such a way can be invoked without parameteres and comunicates with dev_mgmt_daemon via
the Unix Domain socket.

You should see printouts that all of the function calls successfully executed:

```
 host initialization success
 performing reset device 0
 device reset operation success
 Subscribed to device connect indication
 Subscribed to device connect-failure indication
 performing connect device 0
 device connect operation success
 waiting for connection complete indication...
 [-- olt 0: Device Indication Received --]
 olt 0: device id [0] connection is complete, system_mode is xgs__2_x, standalone=0
 connection complete
 interface activation operation success
 waiting for interface activation complete indication...
 [-- olt 0: Pon Interface Indication Received for pon 0 --]
 pon interface state change indication success
 pon interface has changed state from inactive to active_working
 interface activation complete
 onu configured
 tm_sched configured
 tm_queue configured
 flow configured
```

### Building the 'clean' target

The other make target supported in this repo is 'clean'.  This target cleans the bal_api repo of all built targets.

To clean the system:

*\> make clean*

### Adding support for user-defined toolchain

The BAL API SDK is released with a built-in support for building on a linux PC using gcc toolchain.
It is possible to add support for additional toolchain(s) in order to build BAL API SDK and application
that will run directly on a linecard.

1. Add file cmake/modules/your-board-name.cmake. Please use cmake/modules/sim.cmake as a reference
2. Build using the following command:
*\> make BOARD=your-board-name*
