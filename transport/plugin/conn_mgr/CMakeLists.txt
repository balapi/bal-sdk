# Transport layer: connection manager plugin
# The plugin uses connection manager services
bcm_module_name(tr_plugin_conn_mgr)
bcm_module_dependencies(PUBLIC transport conn_mgr)
bcm_module_header_paths(PUBLIC .)
bcm_module_definitions(PUBLIC -DBCMTR_UDP_SUPPORT)
bcm_module_srcs(bcmtr_plugin_conn_mgr.c)
bcm_create_lib_target()

