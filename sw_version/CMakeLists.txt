# Software version
bcm_module_name(host_software_version)
bcm_module_header_paths(PUBLIC .)
bcm_create_lib_target()

# Get the version from the header file and add it to the cache. This can be used by any module
# that needs the version in the CMake config stage.
bcm_cache_sw_version(${CMAKE_CURRENT_SOURCE_DIR}/bcmolt_host_sw_version.h
                     ${CMAKE_INSTALL_PREFIX}/fs/release_info.log)

set(HOST_SW_VERSION "${SW_VERSION_MAJOR}.${SW_VERSION_MINOR}.${SW_VERSION_REVISION}" CACHE
    STRING "SW Version Revision" FORCE)

# Add files to the GitHub part of the release tree.
bcm_github_install(./* RELEASE github/sw_version)
