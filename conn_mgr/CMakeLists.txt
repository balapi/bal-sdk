
# Connection manager
#
bcm_module_name(conn_mgr)
bcm_module_dependencies(PUBLIC os dev_log api)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_conn_mgr.c)
if("${OS}" STREQUAL "posix")
    bcm_module_srcs(udp_socket/bcmolt_conn_mgr_udp_socket.c)
endif()
if("${OS}" STREQUAL "threadx")
    bcm_module_header_paths(PUBLIC ./udp_netx)
    bcm_module_dependencies(PUBLIC ip_adapter)
    bcm_module_srcs(udp_netx/bcmolt_conn_mgr_udp_netx.c)
endif()

bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./*
    RELEASE github/conn_mgr
    EXCLUDE_FROM_RELEASE udp_netx)
