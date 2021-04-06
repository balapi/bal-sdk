# API topology support
bcm_module_name(api_topology)
bcm_module_dependencies(PUBLIC system_types)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_api_topology.c)
bcm_create_lib_target()
