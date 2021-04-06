# Generic type TLV-style serializer (used by API layer)

bcm_module_name(serializer)

bcm_module_header_paths(PUBLIC .)
bcm_module_dependencies(PUBLIC os utils metadata)
bcm_module_dependencies(PRIVATE dev_log)
bcm_module_srcs(bcmolt_serializer.c)

bcm_create_lib_target()
