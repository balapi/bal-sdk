# linenoise - simple line editing library
# should work on any VT-100-compatible terminal

bcm_module_name(linenoise)

bcm_module_header_paths(PUBLIC .)
bcm_module_dependencies(PUBLIC os)
bcm_module_definitions(PUBLIC -DCONFIG_LINENOISE -DCONFIG_EDITLINE)
bcm_module_srcs(linenoise.c)

# The following defines should be set for OS that doesn't have support for tty and/or file IO
if(${LINENOISE_DISABLE_IOCTL})
    bcm_module_definitions(PUBLIC -DLINENOISE_DISABLE_IOCTL)
endif()
if(${LINENOISE_DISABLE_TERMIOS})
    bcm_module_definitions(PUBLIC -DLINENOISE_DISABLE_TERMIOS)
endif()
if(${LINENOISE_DISABLE_HIST_SAVE})
    bcm_module_definitions(PUBLIC -DLINENOISE_DISABLE_HIST_SAVE)
endif()

bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/third_party/linenoise)
