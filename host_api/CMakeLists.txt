# Host API initialization support
bcm_module_name(host_api)

bcm_module_dependencies(PUBLIC api api_cli api_impl api_topology dev_log os transport)
if(NOT SIMULATION_BUILD AND NOT OPEN_SOURCE)
    bcm_module_dependencies(PUBLIC bcm_board)
endif()
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_host_init.c)
bcm_create_lib_target(NO_RESET)

#====
# the host software version comes from the CMake cache.
#====
bcm_module_dependencies(RESET)

#====
# Set the default libbal_host_api shared object library name to
# the proprietary name if not already set
#====
set(BAL_HOST_API_NAME bal_host_api-nda_req CACHE STRING "BAL_HOST_API_NAME")

bcm_module_name(${BAL_HOST_API_NAME})
bcm_module_dependencies(PUBLIC api api_impl api_topology dev_log os transport)

#====
# Determine if the API CLI contains source files indicating a linkable library
#====
get_target_property(_API_CLI_TYPE api_cli TYPE)
if(_API_CLI_TYPE STREQUAL "STATIC_LIBRARY")
    bcm_module_dependencies(PUBLIC "-Wl,--whole-archive $<TARGET_FILE:api_cli> -Wl,--no-whole-archive")
endif()

bcm_create_shared_lib_target(fs STRIP)

# Install the libbal_host_api.so as a versioned library
install(CODE "execute_process(COMMAND mv ${CMAKE_INSTALL_PREFIX}/fs/lib${BAL_HOST_API_NAME}.so
        ${CMAKE_INSTALL_PREFIX}/fs/lib${BAL_HOST_API_NAME}.${HOST_SW_VERSION}.so)")
install(CODE "execute_process(COMMAND ln -s lib${BAL_HOST_API_NAME}.${HOST_SW_VERSION}.so
        ${CMAKE_INSTALL_PREFIX}/fs/lib${BAL_HOST_API_NAME}.so)")

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/host_api)
