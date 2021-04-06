# This file contains CMake macros for downloading and building third-party packages
# The macros available to the Aspen module CMakeLists.txt files are:
#
#   - bcm_3rdparty_module_name(<name>, <version>) - Set the 3rd party module name and associated variables.
#       This macro must be the 1st called
#   - bcm_3rdparty_download_wget(<domain> <archive>) - download using wget and unpack 3rd party package.
#   - bcm_3rdparty_build_cmake([targets]) - build using cmake+make.
#       If [targets] is not specified, "install" is used by default"
#   - bcm_3rdparty_build_automake([targets]) - build using configure+make.
#       If [targets] is not specified, "install" is used by default"
#   - bcm_3rdparty_add_build_options(options) - add build options.
#   - bcm_3rdparty_add_cflags(options) - add cflags.
#   - bcm_3rdparty_add_cxxflags(options) - add cxxflags.
#   - bcm_3rdparty_add_ldflags(options) - add ldflags.
#   - bcm_3rdparty_add_dependencies(deps) - add dependencies
#   - bcm_3rdparty_export(ldflags) - export module
#       This is the last macro to be called when building 3rd party package
#

#======
# Macro to set 3rd party package name
#
# @param MODULE_NAME    [in] Target name to add property to.
# @param VERSION        [in] Package version.
#======
macro(bcm_3rdparty_module_name MODULE_NAME VERSION)
    bcm_module_name(${MODULE_NAME})
    string(TOUPPER ${MODULE_NAME} _MOD_NAME_UPPER)
    bcm_make_normal_option(${_MOD_NAME_UPPER}_VERSION STRING "${MODULE_NAME} version" "${VERSION}")

    if(${_MOD_NAME_UPPER}_VERSION)
        set(_VERSION ${${_MOD_NAME_UPPER}_VERSION})
    else()
        set(_VERSION ${VERSION})
    endif()

    set(_${_MOD_NAME_UPPER}_TARGET ${MODULE_NAME}_${${_MOD_NAME_UPPER}_VERSION})
    set(_${_MOD_NAME_UPPER}_INSTALL_TOP ${CMAKE_BINARY_DIR}/fs)

    set(_${_MOD_NAME_UPPER}_LOADED_FILE ${CMAKE_CURRENT_BINARY_DIR}/.${MODULE_NAME}_${_VERSION}_loaded)
    set(_${_MOD_NAME_UPPER}_INSTALLED_FILE ${CMAKE_CURRENT_BINARY_DIR}/.${MODULE_NAME}_${_VERSION}_installed)
    unset(_VERSION)
endmacro(bcm_3rdparty_module_name)

#======
# Macro to download 3rd party package using wget
#
# @param DOMAIN         [in] Domain where to download
# @param ARCHIVE        [in] Package file name
# [@param SRC_DIR]      [in] Package directory name after unpacking
#======
macro(bcm_3rdparty_download_wget DOMAIN ARCHIVE)

    # Absolute path of where the package is going to be unpacked
    if(NOT "${ARGN}" STREQUAL "")
        set(_${_MOD_NAME_UPPER}_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/${ARGN})
    else()
        set(_${_MOD_NAME_UPPER}_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/${_MOD_NAME}-${${_MOD_NAME_UPPER}_VERSION})
    endif()

    # Identify "unpack" command
    get_filename_component(_ARCHIVE_EXT ${ARCHIVE} EXT)
    if("${_ARCHIVE_EXT}" MATCHES ".*.tar.gz")
        set(_UNPACK_COMMAND tar -xzf)
    elseif("${_ARCHIVE_EXT}" MATCHES ".*.tar.bz")
        set(_UNPACK_COMMAND tar -xjf)
    elseif("${_ARCHIVE_EXT}" MATCHES ".*.tar.xz")
        set(_UNPACK_COMMAND tar -xJf)
    elseif("${_ARCHIVE_EXT}" MATCHES ".*.zip")
        set(_UNPACK_COMMAND unzip)
    else()
        message(FATAL_ERROR "Don't know how to unpack archive ${ARCHIVE}")
    endif()

    # Check if patch file exists
    set(_PATCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${_MOD_NAME}_${${_MOD_NAME_UPPER}_VERSION}.patch)
    if(EXISTS ${_PATCH_FILE})
        set(_CMD_PATCH COMMAND patch -p0 -i ${_PATCH_FILE} && echo ${_MOD_NAME} patched)
    endif()

    # Pull archive from public repository only if needed
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ARCHIVE})
        set(_PULL_ARCHIVE_COMMAND COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/${ARCHIVE} .)
    else()
        set(_PULL_ARCHIVE_COMMAND COMMAND wget --no-check-certificate ${DOMAIN}/${ARCHIVE})
    endif()
    add_custom_command(OUTPUT ${_${_MOD_NAME_UPPER}_LOADED_FILE}
        COMMAND echo "Loading ${ARCHIVE} from ${DOMAIN}.."
        COMMAND rm -rf ${_${_MOD_NAME_UPPER}_SRC_DIR} ${DOMAIN}/${ARCHIVE}*
        ${_PULL_ARCHIVE_COMMAND}
        COMMAND ${_UNPACK_COMMAND} ${ARCHIVE}
        COMMAND rm -f ${ARCHIVE}
        COMMAND mkdir -p ${_${_MOD_NAME_UPPER}_SRC_DIR}/build
        COMMAND touch ${_${_MOD_NAME_UPPER}_LOADED_FILE}
        COMMAND echo "${ARCHIVE} loaded and unpacked in ${_${_MOD_NAME_UPPER}_SRC_DIR}"
        ${_CMD_PATCH}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    add_custom_target(_${_MOD_NAME_UPPER}_LOADED DEPENDS ${_${_MOD_NAME_UPPER}_LOADED_FILE})

    unset(_ARCHIVE_EXT)
    unset(_UNPACK_COMMAND)
    unset(_PATCH_FILE)
    unset(_CMD_PATCH)
endmacro(bcm_3rdparty_download_wget)

#======
# Macro to add build options
#
# @param ARGN           [in] options
#======
macro(bcm_3rdparty_add_build_options)
    list(APPEND _${_MOD_NAME_UPPER}_BUILD_OPTS ${ARGN})
endmacro(bcm_3rdparty_add_build_options)

#======
# Macro to add cflags
#
# @param ARGN           [in] options
#======
macro(bcm_3rdparty_add_cflags)
    list(APPEND _${_MOD_NAME_UPPER}_CFLAGS ${ARGN})
endmacro(bcm_3rdparty_add_cflags)

#======
# Macro to add cxxflags
#
# @param ARGN           [in] options
#======
macro(bcm_3rdparty_add_cxxflags)
    list(APPEND _${_MOD_NAME_UPPER}_CXXFLAGS ${ARGN})
endmacro(bcm_3rdparty_add_cxxflags)

#======
# Macro to add ldflags
#
# @param ARGN           [in] options
#======
macro(bcm_3rdparty_add_ldflags)
    list(APPEND _${_MOD_NAME_UPPER}_LDFLAGS ${ARGN})
endmacro(bcm_3rdparty_add_ldflags)

#======
# Macro to add dependencies
#
# @param ARGN           [in] dependencies
#======
macro(bcm_3rdparty_add_dependencies)
    bcm_module_dependencies(PUBLIC ${ARGN})
endmacro(bcm_3rdparty_add_dependencies)

#======
# Macro to add environment variables
#
# @param ARGN           [in] environment variables in format var=value
#======
macro(bcm_3rdparty_add_env_variables)
    list(APPEND _${_MOD_NAME_UPPER}_BUILD_ENV ${ARGN})
endmacro(bcm_3rdparty_add_env_variables)

#======
# Macro to build 3rd party package using cmake+make
#
# @param ARGN           [in] Make targets
#======
macro(bcm_3rdparty_build_cmake)

    string(REPLACE " " ";" _BCM_ARCH_FLAGS_LIST "${BCM_ARCHITECTURE_FLAGS}")
    set(_CFLAGS_OPTS -I"${BUILD_TOP}"/fs/include ${_BCM_ARCH_FLAGS_LIST} ${_${_MOD_NAME_UPPER}_CFLAGS})
    set(_CXXFLAGS_OPTS -I"${BUILD_TOP}"/fs/include ${_BCM_ARCH_FLAGS_LIST} ${_${_MOD_NAME_UPPER}_CXXFLAGS})
    set(_LDFLAGS_OPTS -L"${BUILD_TOP}"/fs/lib ${LINK_FLAGS} ${_${_MOD_NAME_UPPER}_LDFLAGS})
    set(_TARGETS ${ARGN})
    if(NOT _TARGETS)
        set(_TARGETS install)
    endif()
    set(_LD_LIBRARY_PATH "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/fs/lib")
    if(NOT BCM_CONFIG_HOST MATCHES "x86")
        set(_LD_LIBRARY_PATH "${_LD_LIBRARY_PATH}:${CMAKE_BINARY_DIR}/../host-sim/fs/lib")
    endif()

    add_custom_command(OUTPUT ${_${_MOD_NAME_UPPER}_INSTALLED_FILE}
        COMMAND echo "Building ${_MOD_NAME}-${${_MOD_NAME_UPPER}_VERSION}.."
        COMMAND PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/fs/lib/pkgconfig ${_${_MOD_NAME_UPPER}_BUILD_ENV} ${CMAKE_COMMAND} ..
            -DCMAKE_INSTALL_PREFIX=${_${_MOD_NAME_UPPER}_INSTALL_TOP}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DCMAKE_AR=${CMAKE_AR} -DCMAKE_LINKER=${CMAKE_LINKER}
            -DCMAKE_C_FLAGS="${_CFLAGS_OPTS}" -DCMAKE_CXX_FLAGS="${_CXXFLAGS_OPTS}"
            -DCMAKE_EXE_LINKER_FLAGS="${_LDFLAGS_OPTS}"
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=${CMAKE_VERBOSE_MAKEFILE}
            ${_${_MOD_NAME_UPPER}_BUILD_OPTS}
        COMMAND ${_LD_LIBRARY_PATH} ${_${_MOD_NAME_UPPER}_BUILD_ENV} ${CMAKE_MAKE_PROGRAM} ${MAKE_JOB_FLAG} ${_BCM_COMMON_MAKE_FLAGS} MAKEOVERRIDES= ${_TARGETS}
        COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/.${_MOD_NAME}_*_installed
        COMMAND touch ${_${_MOD_NAME_UPPER}_INSTALLED_FILE}
        DEPENDS ${_MOD_PUBLIC_DEPS} ${_${_MOD_NAME_UPPER}_LOADED_FILE}
        WORKING_DIRECTORY ${_${_MOD_NAME_UPPER}_SRC_DIR}/build)

    unset(_BCM_ARCH_FLAGS_LIST)
    unset(_CFLAGS_OPTS)
    unset(_CXXFLAGS_OPTS)
    unset(_LDFLAGS_OPTS)
    unset(_TARGETS)

endmacro(bcm_3rdparty_build_cmake)

#======
# Macro to build 3rd party package using automake tools+make
#
# @param ARGN           [in] Make targets
#======
macro(bcm_3rdparty_build_automake)

    string(REPLACE " " ";" _BCM_ARCH_FLAGS_LIST "${BCM_ARCHITECTURE_FLAGS}")
    set(_CFLAGS_OPTS -I"${BUILD_TOP}"/fs/include ${_BCM_ARCH_FLAGS_LIST} ${_${_MOD_NAME_UPPER}_CFLAGS})
    set(_CXXFLAGS_OPTS -I"${BUILD_TOP}"/fs/include ${_BCM_ARCH_FLAGS_LIST} ${_${_MOD_NAME_UPPER}_CXXFLAGS})
    set(_LDFLAGS_OPTS -L"${BUILD_TOP}"/fs/lib ${LINK_FLAGS} ${_${_MOD_NAME_UPPER}_LDFLAGS})
    if(NOT DEFINED BCM_CONFIG_HOST)
        message(FATAL_ERROR "Need to add support for board ${BOARD}")
    endif()
    if(DEFINED ${_MOD_NAME_UPPER}_CONFIG_HOST)
        set(_CONFIG_HOST ${${_MOD_NAME_UPPER}_CONFIG_HOST})
    else()
        set(_CONFIG_HOST ${BCM_CONFIG_HOST})
    endif()
    set(_TARGETS ${ARGN})
    if(NOT _TARGETS)
        set(_TARGETS install)
    endif()
    if(NOT ${_MOD_NAME_UPPER}-DO_NOT_RECONF)
        set(_RECONF_CMD COMMAND aclocal && libtoolize && autoheader && automake --add-missing && autoconf)
    endif()

    add_custom_command(OUTPUT ${_${_MOD_NAME_UPPER}_INSTALLED_FILE}
        COMMAND echo "Building ${_MOD_NAME}-${${_MOD_NAME_UPPER}_VERSION}.."
        ${_RECONF_CMD}
        COMMAND ./configure --prefix=${_${_MOD_NAME_UPPER}_INSTALL_TOP} --host=${_CONFIG_HOST}
            CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER}
            CFLAGS="${_CFLAGS_OPTS}" CXXFLAGS="${_CXXFLAGS_OPTS}"
            LDFLAGS="${_LDFLAGS_OPTS}" ${_${_MOD_NAME_UPPER}_BUILD_OPTS}
        COMMAND ${CMAKE_MAKE_PROGRAM} ${MAKE_JOB_FLAG} ${_BCM_COMMON_MAKE_FLAGS} MAKEOVERRIDES= ${_TARGETS}
        COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/.${_MOD_NAME}_*_installed
        COMMAND touch ${_${_MOD_NAME_UPPER}_INSTALLED_FILE}
        DEPENDS ${_MOD_PUBLIC_DEPS} ${_${_MOD_NAME_UPPER}_LOADED_FILE}
        WORKING_DIRECTORY ${_${_MOD_NAME_UPPER}_SRC_DIR})

    unset(_BCM_ARCH_FLAGS_LIST)
    unset(_CFLAGS_OPTS)
    unset(_CXXFLAGS_OPTS)
    unset(_LDFLAGS_OPTS)
    unset(_TARGETS)
    unset(_CONFIG_HOST)
    unset(_RECONF_CMD)

endmacro(bcm_3rdparty_build_automake)

#======
# Macro to build 3rd dummy party package
#
# @param ARGN           [in] Make targets
#======
macro(bcm_3rdparty_build_dummy)
    set(_DEPENDENCIES ${_MOD_PUBLIC_DEPS})
    if(TARGET _${_MOD_NAME_UPPER}_LOADED)
        set(_DEPENDENCIES ${_DEPENDENCIES} _${_MOD_NAME_UPPER}_LOADED)
    endif()
    add_custom_command(OUTPUT ${_${_MOD_NAME_UPPER}_INSTALLED_FILE}
        COMMAND echo "Building ${_MOD_NAME}-${${_MOD_NAME_UPPER}_VERSION}.."
        COMMAND touch ${_${_MOD_NAME_UPPER}_INSTALLED_FILE}
        DEPENDS ${_DEPENDENCIES}
        WORKING_DIRECTORY ${_${_MOD_NAME_UPPER}_SRC_DIR})
endmacro(bcm_3rdparty_build_dummy)

#======
# Macro to export 3rd party package
#
# @param ARG0           [in] List of libraries (';'-delimited, without -l)
# @param ARG1-N         [in] Link options
#======
macro(bcm_3rdparty_export)

    if(NOT _${_MOD_NAME_UPPER}_TYPE)
        set(_${_MOD_NAME_UPPER}_TYPE SHARED_LIBRARY)
    endif()

    unset(_LIBS)
    unset(_LFLAGS)
    if("${_${_MOD_NAME_UPPER}_TYPE}" MATCHES ".*_LIBRARY")
        if(NOT "${ARGV}" STREQUAL "")
            set(_ARG_LIST ${ARGV})
            list(GET _ARG_LIST 0 _LIBS)
            # The 1st parameter might be an empty string. In this case remove it
            if(NOT _LIBS)
                unset(_LIBS)
            endif()
            list(REMOVE_AT _ARG_LIST 0)
            foreach(_OPT ${_ARG_LIST})
                list(APPEND _LFLAGS ${_OPT})
            endforeach(_OPT)
        else()
            # Derive library name from module name
            if("${_MOD_NAME}" MATCHES "lib.*")
                string(SUBSTRING ${_MOD_NAME} 3 -1 _LIBS)
            else()
                set(_LIBS ${_MOD_NAME})
            endif()
        endif()
    endif()

    add_custom_target(${_${_MOD_NAME_UPPER}_TARGET} DEPENDS ${_${_MOD_NAME_UPPER}_INSTALLED_FILE})
    add_library(${_MOD_NAME} INTERFACE)
    add_dependencies(${_MOD_NAME} ${_${_MOD_NAME_UPPER}_TARGET})

    if(_LIBS)
        target_include_directories(${_MOD_NAME} INTERFACE ${BUILD_TOP}/fs/include)
        if("${_${_MOD_NAME_UPPER}_CFLAGS}")
            target_compile_options(${_MOD_NAME} INTERFACE ${_${_MOD_NAME_UPPER}_CFLAGS})
        endif()
        target_link_libraries(${_MOD_NAME} INTERFACE ${_LIBS})
        # For some reason target_link_libraries is not reliable. Adding libraries explicitly
        set(_LOPTS -L${BUILD_TOP}/fs/lib -Wl,-rpath=${BUILD_TOP}/fs/lib ${_LFLAGS})
        foreach(_LIB ${_LIBS})
            list(APPEND _LOPTS -l${_LIB})
        endforeach(_LIB)
        set_target_properties(${_MOD_NAME} PROPERTIES INTERFACE_SYSTEM_LIBRARIES "${_LOPTS}")
    endif()
    if(_MOD_PUBLIC_DEPS)
        add_dependencies(${_${_MOD_NAME_UPPER}_TARGET} ${_MOD_PUBLIC_DEPS})
    endif()

    set_target_properties(${_${_MOD_NAME_UPPER}_TARGET} PROPERTIES IMPORT_TYPE ${_${_MOD_NAME_UPPER}_TYPE})

    # Unset all variables
    unset(_CFLAGS)
    unset(_LFLAGS)
    unset(_LIBRARY_TYPE)
    unset(_LIBS)
    unset(_DEPS)
    unset(_${_MOD_NAME}_LIBRARY_TYPE)
    unset(_${_MOD_NAME}_LFLAGS)
    unset(${_MOD_NAME_UPPER}_VERSION)
    unset(_${_MOD_NAME_UPPER}_TARGET)
    unset(_${_MOD_NAME_UPPER}_INSTALL_TOP)
    unset(_${_MOD_NAME_UPPER}_LOADED_FILE)
    unset(_${_MOD_NAME_UPPER}_INSTALLED_FILE)
    unset(${_MOD_NAME_UPPER})
    _bcm_module_globals_clear()
endmacro(bcm_3rdparty_export)
