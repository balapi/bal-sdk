# Current OLT selector (for CLI)
bcm_module_name(olt_selector)
bcm_module_dependencies(PUBLIC cli api api_topology)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_olt_selector.c)
bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/olt_selector)
