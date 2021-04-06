bcm_module_name(system_types)

bcm_module_dependencies(PUBLIC os utils)
bcm_module_header_paths(PUBLIC .)

bcm_create_lib_target()

# Add additional subdirectories for this module
bcm_add_subdirectory(funcs)
