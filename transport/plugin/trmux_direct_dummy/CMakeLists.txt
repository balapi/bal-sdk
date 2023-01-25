# Transport layer: dummy trmux integration plugin
# It is used to satisfy link for host application
bcm_module_name(tr_plugin_trmux_direct_dummy)
bcm_module_dependencies(PUBLIC transport tr_plugin_trmux_direct_HDRONLY)
bcm_module_srcs(bcmtr_plugin_trmux_direct_dummy.c)
bcm_create_lib_target()
