# API PON interface and device translation support
bcm_module_name(api_translation)
bcm_module_dependencies(PUBLIC api api_topology transport api_conn_mgr)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_api_translation.c)
bcm_create_lib_target()
