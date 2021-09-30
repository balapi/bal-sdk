# Top level CMakeLists.txt defining the build project for the BCM686xx products

#====
# Indicate the minimum version of CMake required
#====
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

#====
# Identify where to find the modules
#====
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

#====
# Set a project version. Really doesn't matter what we use here, but it could be release related if we want
#====
set(PROJECT_VERSION 3.0.0)

#====
# Define the project we are building for
#====
project(bcm686xx
        VERSION ${PROJECT_VERSION}
        LANGUAGES CXX C ASM)

#====
# Set global variables used here
#====
set(SOURCE_TOP ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_TOP ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${BUILD_TOP})

#====
# Add the CMake modules we use here
#====
include(utils)
include(common_definitions)
include(build_macros)
include(optional_macros)           # Include any optional macros used for internal testing

#====
# Set the libbal_host_api shared object library name (oss)
#====
set(BAL_HOST_API_NAME bal_host_api-oss CACHE STRING "BAL_HOST_API_NAME" FORCE)

#====
# Add the top level subdirectories we need to add
#====
bcm_add_subdirectory(os_abstraction)
bcm_add_subdirectory(config)
bcm_add_subdirectory(utils)
bcm_add_subdirectory(dev_log)
bcm_add_subdirectory(conn_mgr)
bcm_add_subdirectory(system_types)
bcm_add_subdirectory(cli)
bcm_add_subdirectory(transport)
bcm_add_subdirectory(api)
bcm_add_subdirectory(api_conn_mgr)
bcm_add_subdirectory(metadata)
bcm_add_subdirectory(api_cli)
bcm_add_subdirectory(api_log)
bcm_add_subdirectory(olt_selector)
bcm_add_subdirectory(sw_version)
bcm_add_subdirectory(host_api)
bcm_add_subdirectory(third_party/linenoise)
bcm_add_subdirectory(examples)

#====
# Post processing support to make the custom properties transitive
#====
include(post_process)
bcm_flatten_transitive_dependencies()

# Create build/fs/include directory with copies of .h files
add_custom_target(github_install_include
        COMMAND mkdir -p ${BUILD_TOP}/fs/include
        COMMAND find ${SOURCE_TOP} -path ${BUILD_TOP} -prune -o -name '*.h' -type f -exec cp -f \\{\\} ${BUILD_TOP}/fs/include/ \\\;
        WORKING_DIRECTORY ${SOURCE_TOP})
