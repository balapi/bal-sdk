# API logger
bcm_module_name(api_log)
bcm_module_dependencies(PUBLIC dev_log api metadata)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_api_log.c)
bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/api_log)
