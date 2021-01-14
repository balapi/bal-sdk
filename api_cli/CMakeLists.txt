    bcm_module_name(api_cli)
	bcm_module_dependencies(PUBLIC cli)
	bcm_module_header_paths(PUBLIC .)

if(${CLI})
	bcm_module_dependencies(PUBLIC utils api api_impl olt_selector)
    bcm_module_cflags(PRIVATE -Wframe-larger-than=20480)

	bcm_module_srcs(bcm_api_cli.c
                    bcmolt_api_cli_handlers.c)
endif()

    bcm_create_lib_target()

