# API connection manager
bcm_module_name(api_conn_mgr)
bcm_module_header_paths(PUBLIC .)
bcm_module_dependencies(PUBLIC os api transport api_translation host_software_version)
bcm_module_srcs(bcmolt_api_conn_mgr.c)
bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/api_conn_mgr)
