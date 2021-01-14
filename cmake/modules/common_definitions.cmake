# This file is included first in the top level CMakeLists.txt file to provide common definitions for all
# builds. There should be no platform/board/compiler specific settings in this file.

#====
# Common definitions
#====
set(SUBSYSTEM host)

#====
# Skip the install of symbols in the 'fs' directory for the release
#====
set(BCM_INSTALL_STRIP_SYMBOLS n CACHE BOOL "Do not install stripped symbols" FORCE)

#====
# Add a subdirectory within the Aspen system. This is a wrapper on the CMake add_subdirectory that collects
# information on which directories have been added.
#
# @param DIR            [in] Directory to add. Can be relative or absolute
# @param OPTIONAL       [in] Optional argument indicating it is OK if the directory is not there
#====
macro(bcm_add_subdirectory DIR)
    bcm_find_absolute_path(_BCM_ABSOLUTE_DIR ${DIR})

    if(IS_DIRECTORY ${_BCM_ABSOLUTE_DIR})
        add_subdirectory(${DIR})
    else()
        # See if the directory is 'optional' or 'exclude_from_release'; otherwise, fatal error
        set(_MY_ARGN ${ARGN})
        list(FIND _MY_ARGN OPTIONAL _OPTIONAL_INDEX)
        list(FIND _MY_ARGN EXCLUDE_FROM_RELEASE _EXCLUDE_INDEX)
        if((${_OPTIONAL_INDEX} LESS 0) AND (${_EXCLUDE_INDEX} LESS 0))
            bcm_message(FATAL_ERROR "ERROR: Sub-directory, '${DIR}', does not exist")
        endif()
    endif()
endmacro(bcm_add_subdirectory)

#====
# This is the release directory so we ignore any calls to bcm_release_install
#====
function(bcm_release_install)
endfunction(bcm_release_install)

function(bcm_github_install)
endfunction(bcm_github_install)

#====
# Common compile definitions for all builds
#====
bcm_create_global_compile_definition(BCM_SUBSYSTEM ${SUBSYSTEM})

#====
# CMake checks for unused variables from the command-line. Add intentionally unused variables here.
#====
set(IGNORED_CLI_ARGS ${CMAKE_TOOLCHAIN_FILE} ${MAKE_JOB_FLAG})

if(NOT OPEN_SOURCE)
#====
# If the kernel directory exists, create a dummy target for the module dependencies
#====
if(IS_DIRECTORY ${KERNEL_OUTDIR})
    add_custom_target(kernel)
    set_target_properties(kernel PROPERTIES KERNEL_OUTDIR ${KERNEL_OUTDIR})
elseif(NOT SIMULATION_BUILD)
    bcm_message(FATAL_ERROR "ERROR: Kernel objects directory not found: KERNEL_OUTDIR=${KERNEL_OUTDIR}")
endif()
endif()

#====
# If the main board is not set explicitly, it defaults to BOARD
#====
if(NOT MAIN_BOARD)
    set(MAIN_BOARD ${BOARD})
endif()
