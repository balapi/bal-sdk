# Functions (e.g. pack/unpack) that operate on common system types.

bcm_module_name(system_type_funcs)

bcm_module_dependencies(PUBLIC os utils system_types)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_system_types_enum_funcs.c
                bcmolt_system_types_struct_funcs.c)

bcm_create_lib_target()
