# Host API initialization support
bcm_module_name(host_api)

bcm_module_dependencies(PUBLIC api api_impl api_topology dev_log os transport)
if(NOT SIMULATION_BUILD AND NOT OPEN_SOURCE)
    bcm_module_dependencies(PUBLIC bcm_board)
endif()
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_host_init.c)
bcm_create_lib_target(NO_RESET)

#====
# the host software version comes from the CMake cache.
#====
if(${OPEN_SOURCE})
    # Create the libbal_host_api shared object library
    bcm_module_name(bal_host_api)
    bcm_create_shared_lib_target(fs STRIP)

    # Install the libbal_host_api.so as a versioned library
    install(CODE "execute_process(COMMAND mv ${CMAKE_INSTALL_PREFIX}/fs/libbal_host_api.so
        ${CMAKE_INSTALL_PREFIX}/fs/libbal_host_api.${HOST_SW_VERSION}.so)")
    install(CODE "execute_process(COMMAND ln -s libbal_host_api.${HOST_SW_VERSION}.so
        ${CMAKE_INSTALL_PREFIX}/fs/libbal_host_api.so)")

    # Add files to the GitHub part of the release tree.
    bcm_github_install(./* RELEASE github/host_api)
endif()
