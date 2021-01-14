# Make option for enabling/disabling logger
bcm_make_normal_option(LOG   BOOL    "Enable host side logger" y)

bcm_module_name(dev_log)
bcm_module_header_paths(PUBLIC .)

# ENABLE_LOG is always set in embedded side.
if("${SUBSYSTEM}" STREQUAL "embedded")
    bcm_module_definitions(PUBLIC -DENABLE_LOG)
    set(LOG "y" PARENT_SCOPE)
    set(LOG "y")
endif()

if(${LOG})
	bcm_module_dependencies(PUBLIC os cli utils)

	bcm_make_debug_option(LOG_DEBUG  BOOL    "Enable Dev Log Debugging" n)
	bcm_make_debug_option(LOG_TRIGGER  BOOL    "Enable Dev Log Trigger Feature" n)

    if("${OS}" STREQUAL "posix")
		bcm_make_normal_option(LOG_SYSLOG  BOOL    "Enable logging to syslog" y)
		if(${LOG_SYSLOG})
			bcm_module_definitions(PUBLIC -DDEV_LOG_SYSLOG)
		endif()
    endif()

	bcm_module_definitions(PUBLIC -DENABLE_LOG)

	if(${LOG_DEBUG})
		bcm_module_definitions(PRIVATE -DDEV_LOG_DEBUG)
	endif()

	if(${LOG_TRIGGER})
		bcm_module_definitions(PRIVATE -DTRIGGER_LOGGER_FEATURE)
	endif()

	bcm_module_srcs(bcm_dev_log.c bcm_dev_log_task.c)

	if(${CLI})
		bcm_module_srcs(bcm_dev_log_cli.c)
	endif()

	if("${TOOLCHAIN}" STREQUAL "gcc")
		bcm_module_cflags(PRIVATE -Wno-format-security)
	endif()

endif()

bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/dev_log)
