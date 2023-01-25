
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
        bcm_make_debug_option(TRANSPORT_PERFTEST    BOOL    "Enable transport performance test" y)
    endif()
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

bcm_create_lib_target()

# Add additional subdirectories for this module
bcm_add_subdirectory(plugin)

# Host is used in the release package
bcm_add_subdirectory(host OPTIONAL)

# Add files to the GitHub part of the release tree.
bcm_github_install(./*
                   RELEASE github/transport
                   EXCLUDE_FROM_RELEASE test bcmtr_transport_embedded.c)
