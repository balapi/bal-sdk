# Make option for enabling/disabling CLI
bcm_make_normal_option(CLI   BOOL    "Enable host side CLI" y)

bcm_module_name(cli)
bcm_module_header_paths(PUBLIC .)

# ENABLE_CLI is always set in embedded side.
if("${SUBSYSTEM}" STREQUAL "embedded")
    bcm_module_definitions(PUBLIC -DENABLE_CLI)
    set(CLI "y" PARENT_SCOPE)
    set(CLI "y")
endif()

if(${CLI})
    bcm_module_dependencies(PUBLIC os utils)
    if(NOT OPEN_SOURCE)
        bcm_module_dependencies(PUBLIC metadata)
    endif()
    bcm_module_definitions(PUBLIC -DENABLE_CLI)
    bcm_make_normal_option(CLI_LINENOISE    BOOL    "Enable linenoise CLI integration" y)

    if(${CLI_LINENOISE})
        bcm_module_dependencies(PRIVATE linenoise)
    endif()

    bcm_module_srcs(bcmcli_session.c bcmcli.c)
endif()

bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./*
    RELEASE github/cli
    EXCLUDE_FROM_RELEASE unitest)
