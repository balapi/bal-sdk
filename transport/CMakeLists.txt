
# Transport layer
bcm_module_name(transport)
bcm_module_header_paths(PUBLIC .)
bcm_module_dependencies(PUBLIC utils api dev_log conn_mgr api_cli tr_plugin_conn_mgr)

bcm_module_srcs(bcmtr_transport.c bcmtr_config.c bcmtr_debug.c)

if("${SUBSYSTEM}" STREQUAL "host" OR "${SUBSYSTEM}" STREQUAL "opencpu")
    if("${OS_KERNEL}" STREQUAL "linux")
        bcm_module_dependencies(PUBLIC dev_log_linux)
    endif()
    if("${OS}" STREQUAL "posix")
        bcm_module_dependencies(PUBLIC tr_plugin_ud)
    endif()
    if(NOT OPEN_SOURCE)
        bcm_module_dependencies(PUBLIC tr_plugin_trmux_direct)
    endif()
else()
    if("${OS}" STREQUAL "threadx")
        bcm_module_dependencies(PUBLIC tr_plugin_pcie)
    endif()
endif()

if(${CLI})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test)
        bcm_make_debug_option(TRANSPORT_PERFTEST                BOOL   "Enable transport performance test" y)
    endif()
    # AUTO_CLD_CAPTURE_BUF_SIZE_BYTES is applicable only to the embedded side, because in the host side there is already a "playback" user application that uses the capture buffer from init time
    # (so it cannot be initialized twice).
    bcm_make_debug_option(AUTO_CLD_CAPTURE_BUF_SIZE_BYTES       STRING "Enable Capture CLD automatically during init time by specifying the capture buffer size in bytes (embedded side only)" 0)
    bcm_make_debug_option(AUTO_CLD_LOG                          BOOL   "Enable Log CLD automatically during init time" n)
    bcm_make_debug_option(AUTO_CLD_DUMP                         BOOL   "Enable Dump CLD automatically during init time" n)
    bcm_make_debug_option(AUTO_CLD_CLI                          BOOL   "Enable CLI CLD automatically during init time" n)
    bcm_make_debug_option(AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT BOOL   "Output CLI CLD via bcmcli_session_print() instead of the logger (currently applicable only for CLI CLD)" n)
    bcm_make_debug_option(AUTO_CLD_EXCLUDE_GET                  BOOL   "Exclude GET requests" n)
    bcm_make_debug_option(AUTO_CLD_EXCLUDE_DEVICE_KEEP_ALIVE    BOOL   "Exclude device keepalive requests" n)
    bcm_make_debug_option(AUTO_CLD_EXCLUDE_CPU_PACKETS          BOOL   "Exclude CPU packets (including OMCI)" n)
    bcm_module_srcs(bcmtr_transport_cli.c bcmtr_debug_cli.c)
else()
	set(TRANSPORT_PERFTEST n)
endif()

# Performance test
if(${TRANSPORT_PERFTEST})
	bcm_module_srcs(test/bcmtr_perftest.c)
	bcm_module_header_paths(PUBLIC test)
	bcm_module_definitions(PUBLIC -DBCMTR_PERFTEST)
endif()

if("${SUBSYSTEM}" STREQUAL "embedded" AND NOT "${AUTO_CLD_CAPTURE_BUF_SIZE_BYTES}" STREQUAL "0")
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_CAPTURE_BUF_SIZE_BYTES=${AUTO_CLD_CAPTURE_BUF_SIZE_BYTES})
endif()

if(${AUTO_CLD_LOG})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_LOG)
endif()

if(${AUTO_CLD_DUMP})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_DUMP)
endif()

if(${AUTO_CLD_CLI})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_CLI)
endif()

if(${AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT)
endif()

if(${AUTO_CLD_EXCLUDE_GET})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_EXCLUDE_GET)
endif()

if(${AUTO_CLD_EXCLUDE_DEVICE_KEEP_ALIVE})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_EXCLUDE_DEVICE_KEEP_ALIVE)
endif()

if(${AUTO_CLD_EXCLUDE_CPU_PACKETS})
    bcm_module_definitions(PRIVATE -DCONFIG_AUTO_CLD_EXCLUDE_CPU_PACKETS)
endif()

bcm_create_lib_target()

# Add additional subdirectories for this module
bcm_add_subdirectory(plugin)

# Host is used in the release package
bcm_add_subdirectory(host OPTIONAL)

# Add files to the GitHub part of the release tree.
bcm_github_install(./*
                   RELEASE github/transport
                   EXCLUDE_FROM_RELEASE test bcmtr_transport_embedded.c)
