bcm_module_name(host_config)
bcm_module_header_paths(PUBLIC .)
bcm_create_lib_target()

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/config EXCLUDE_FROM_RELEASE TODO.REVIEW.txt)

# Install the bal_config.ini when building for release
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bal_config.ini)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/bal_config.ini DESTINATION fs)
endif()
