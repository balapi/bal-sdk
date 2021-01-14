# Transport layer: Unix domain socket plugin
if("${OS}" STREQUAL "posix")
    bcm_module_name(tr_plugin_ud)
    bcm_module_definitions(PUBLIC -DPLUGIN_UNIX_DOMAIN)
    bcm_module_dependencies(PUBLIC transport)
    bcm_module_header_paths(PUBLIC .)
    bcm_module_srcs(bcmtr_plugin_unix_domain.c)
    bcm_create_lib_target()

    bcm_github_install(./* RELEASE github/transport/plugin/unix_domain)
endif()
