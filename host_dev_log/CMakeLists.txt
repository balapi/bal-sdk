# Host dev log
bcm_module_name(host_dev_log)
bcm_module_dependencies(PUBLIC os dev_log)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_host_dev_log.c)
bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/host_dev_log)
