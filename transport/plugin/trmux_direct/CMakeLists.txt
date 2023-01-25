# Transport layer: direct transport layer - trmux integration plugin
bcm_module_name(tr_plugin_trmux_direct)
bcm_module_definitions(PUBLIC -DPLUGIN_TRMUX_DIRECT)
bcm_module_dependencies(PUBLIC os api trmux)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmtr_plugin_trmux_direct.c)
bcm_create_lib_target()
