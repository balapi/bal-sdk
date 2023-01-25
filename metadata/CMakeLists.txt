# Generic data metadata library (for APIs, etc)
bcm_module_name(metadata)

bcm_module_header_paths(PUBLIC .)
bcm_module_dependencies(PUBLIC os utils system_types)
bcm_module_srcs(bcmolt_type_metadata.c bcmolt_set_metadata.c bcmolt_metadata_writer.c bcmolt_metadata_utils.c)
if(${CLI})
    bcm_module_dependencies(PUBLIC cli)
    bcm_module_srcs(bcmolt_metadata_cli.c)
endif()
bcm_create_lib_target()

bcm_add_subdirectory(serializer)

# github installation
bcm_github_install(./*
    RELEASE github/metadata
    EXCLUDE_FROM_RELEASE serializer/unitest)
