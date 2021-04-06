# Host-side API implementation
bcm_module_name(api_impl)
bcm_module_dependencies(PUBLIC api api_translation api_conn_mgr transport)
bcm_module_srcs(bcmolt_api.c bcmolt_api_tags.c)
bcm_create_lib_target()

# Add additional subdirectories for this module
bcm_add_subdirectory(topology)
bcm_add_subdirectory(translation)

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/api/host)
