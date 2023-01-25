# Common API
if(OPEN_SOURCE AND NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.open_source_api)
    message(FATAL_ERROR "This is a proprietary API. Can't build with OPEN_SOURCE=y")
endif()

bcm_module_name(api)

bcm_module_dependencies(PUBLIC os utils serializer system_types system_type_funcs dev_log)
bcm_module_header_paths(PUBLIC .)
bcm_module_srcs(bcmolt_msg_pack.c
                bcmolt_api_model_tags.c
                bcmolt_api_writer.c
                bcmolt_api_utils.c
                bcmolt_msg.c
                bcmolt_api_model_api_struct_funcs.c
                bcmolt_api_model_supporting_enum_funcs.c
                bcmolt_api_model_supporting_struct_funcs.c
                bcmolt_api_metadata.c
                bcmolt_api_model_internal.c
                bcmolt_api_code_helper.c)

bcm_create_lib_target()

# Add the library in the host directory
bcm_add_subdirectory(host)
