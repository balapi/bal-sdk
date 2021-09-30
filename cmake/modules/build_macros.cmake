# This file contains CMake macros for building the different module types. This file is included
# in the top level CMakeLists.txt file so that the macros area available to all subdirectories.
# The macros available to the Aspen module CMakeLists.txt files are:
#
#   - bcm_module_name(<name>) - Set the Aspen module name. The macro sets the global variable _MOD_NAME.
#       Equivalent to the Make 'MOD_NAME'.
#   - bcm_module_srcs([RESET] <src files>) - Set the module sources. The source files can be C, C++ or Assembly
#       files. The macro appends the source to a global list, _MOD_SRCS, which is then used in rule creation.
#       This macro can be called multiple times in a CMakeLists.txt file with additional source files. Equivalent
#       to the Make 'srcs'. If the macro is called with the optional RESET parameter, it will reset the global.
#   - bcm_module_header_paths(<PUBLIC|PRIVATE|RESET> <paths>) - Set the header paths to include. These can be
#       public (included for libraries that have a dependency on this one) or private (only available
#       for this library). The paths do not include the -I. The macro appends the paths to a global list,
#       _MOD_PUBLIC_HDR or _MOD_PRIVATE_HDR, which are then used in rule creation. This macro can be called
#       multiple times in a CMakeLists.txt file with additional paths. Equivalent to the Make 'MOD_INC_DIRS' when
#       used with PUBLIC and the Make 'EXTRA_INCLUDES' when used with PRIVATE. If the macro is called with the
#       optional RESET parameter, it will reset the global.
#   - bcm_module_dependencies(<PUBLIC|PRIVATE|RESET> <dependencies>) - Add target dependencies. These can be
#       public (included for libraries that have a dependency on this one) or private (only available
#       for this library). The macro appends the dependencies to a global list, _MOD_PUBLIC_DEPS or _MOD_PRIVATE_DEPS,
#       which are then used in rule creation. This macro can be called multiple times in a CMakeLists.txt file
#       with additional dependencies. Equivalent to the Make 'MOD_DEPS' when used with PUBLIC. If the macro is
#       called with the optional RESET parameter, it will reset the global.
#   - bcm_module_optional_dependencies(<PUBLIC|PRIVATE|RESET> <dependencies>) - Add target dependencies that can
#       be optional. They are only included if the target exists to build them. We check for the target at the
#       end of adding all the sub-directories.
#   - bcm_module_kernel_dependencies(<PUBLIC|PRIVATE> <dependencies>) - Add kernel dependencies which will pull
#       in source files from linux library targets or Module.symvers from linux module targets. These are the
#       dependencies that are part of the 'make' command formed to do the kernel build. If PUBLIC is used, then
#       header-only dependencies are also added as PUBLIC dependencies on the target.
#   - bcm_module_sys_libraries(<library names>) - Add system libraries (e.g. pthread) to the list of libraries
#       we link with. These will only be valid with Linux builds, using gcc. The system libraries are added
#       to the link command after the -Wl,--end-group.
#   - bcm_module_cflags(<PUBLIC|PRIVATE|RESET> <cflags>)  - Set the compile flags to use beyond the default.
#       This does not include the -D definitions as they are handled by bcm_module_definitions() macro.
#       These can be public (included for libraries that have a dependency on this one) or private (only available
#       for this library). The macro appends the cflags to a global list, _MOD_PUBLIC_CFLAGS or _MOD_PRIVATE_CFLAGS,
#       which are then used in rule creation. This macro can be called multiple times in a CMakeLists.txt file
#       with additional compile flags. Equivalent to the Make 'EXTRA_CFLAGS' when used with PRIVATE. If the macro
#       is called with the optional RESET parameter, it will reset the global.
#   - bcm_module_definitions(<PUBLIC|PRIVATE|RESET> <definitions>)  - Set the -D options for the module and must
#       include the '-D'. These can be public (included for libraries that have a dependency on this one) or private
#       (only available for this library). The macro appends the definitions to a global list, _MOD_PUBLIC_DEFS or
#       _MOD_PRIVATE_DEFS, which are then used in rule creation. This macro can be called multiple times in a
#       CMakeLists.txt file with additional definitions. Equivalent to the Make 'MOD_DEFS' when used with PUBLIC.
#       If the macro is called with the optional RESET parameter, it will reset the global.
#   - bcm_module_asm_definitions(<definitions>)  - Set the -D options for the module and must include
#       the '-D'. These are specifically for assembler definitions and are only supported as 'private'. They
#       update the BCM_ASFLAGS locally, so the context is only for the calling module.
#   - bcm_module_codegen_output(<paths from custom command>) - The code generation macro calls this one
#       to get the output of the custom command that generates the .c/.h files from the model. This is done
#       so the bcm_create_*_target() can add a custom target with that output to the target being created.
#       Fixes an issue where multiple modules reference generated .h files before they get created.
#   - bcm_module_function_overrides(<functions>) - Append to the list of functions that this module "wraps", or overrides.
#       This uses the GCC linker --wrap functionality. The modifications to the linker flags will apply to
#       any executable that depends on the current module.
#
#   - bcm_create_lib_target([NO_RESET]) - Create the rule for building a static library. This macro can
#       optionally have the 'NO_RESET' parameter to keep the target creation from clearing all the global
#       variables. This can be used when defining multiple targets in a single CMakeLists.txt file. The
#       macro will make use of any global variables set by using the bcm_moudle_... macros, above.
#   - bcm_create_shared_lib_target() -  Create the rule for building a shared library. This macro has an optional
#       parameter to indicate the directory to install the resulting library. It will also use the globals created by
#       the macros above. This macro call needs to be at the end of the CMakeLists.txt file after any of the
#       bcm_module macros, above.
#   - bcm_create_app_target() - Create the rule for building an application. This macro has an optional parameter
#       to indicate the directory to install the resulting executable. It will also use the globals created by
#       the macros above. This macro call needs to be at the end of the CMakeLists.txt file after any of the
#       bcm_module macros, above.
#   - bcm_create_native_lib_target() - Create the rule for building a library using the native compiler.
#       This macro is used for building code generation tools where the resulting tool needs to run on the
#       build server, regardless of the cross-compile options.
#   - bcm_create_native_app_target() - Create the rule for building an application using the native compiler.
#       This macro is used for building code generation tools where the resulting tool needs to run on the
#       build server, regardless of the cross-compile options.
#   - bcm_create_linux_lib_target() - Create the rule for building a Linux library target. This macro has
#       no parameters, but will use the globals created by the macros above. This macro call needs to be at
#       the end of the CMakeLists.txt file after any of the bcm_module macros, above.
#   - bcm_create_linux_module_target() - Create the rule for building a Linux module. This macro has an optional
#       parameter to indicate the directory to install the resulting module. It will also use the globals
#       created by the macros above. This macro call needs to be at the end of the CMakeLists.txt file after
#       any of the bcm_module macros, above.
#

#======
# Set the Compile and link flags here based on platform/board specific setttings at startup. The
# BCM_<FLAGS> value is set in he cmake/modules/<board|platform>.cmake file.
#======
bcm_stringify_flags(CMAKE_C_FLAGS ${BCM_CFLAGS})
bcm_stringify_flags(CMAKE_CXX_FLAGS ${BCM_CXXFLAGS})
bcm_stringify_flags(CMAKE_ASM_FLAGS ${BCM_ASFLAGS})
bcm_stringify_flags(CMAKE_EXE_LINKER_FLAGS ${BCM_LFLAGS})

# Start with no modules
unset(BCM_ALL_LIB_MODULES         CACHE)
unset(BCM_ALL_APP_MODULES         CACHE)
unset(BCM_ALL_SHARED_LIB_MODULES  CACHE)
unset(BCM_GLOBAL_DEFINITIONS      CACHE)

bcm_make_normal_option(CCACHE BOOL "Enable ccache" y)
if(${CCACHE} AND NOT "${TOOLCHAIN}" STREQUAL "armcc")
    set(CMAKE_C_COMPILER_LAUNCHER ccache)
endif()

bcm_create_global_compile_definition(BCM_OS ${OS})
bcm_make_normal_option(IGNORE_STRIP BOOL "Ignore the STRIP directive on targets and install the target with symbols" n)

# The release build will set this to 'n' to not pollute the install directory
# We don't need this to be a 'make' option, but we want it in the cache.
set(BCM_INSTALL_STRIP_SYMBOLS y CACHE BOOL "Whether to install stipped symbols or not")

# Define the extension to use for header-only libraries we build internally
set(_HEADER_ONLY_EXT    HDRONLY)
set(_KERNEL_EXT         kernel)

#======
# PRIVATE: Add in the current directory as a private header if not set as private or public
#======
function(_bcm_add_default_header_paths)
    set(_ALL_HDRS ${_MOD_PRIVATE_HDR} ${_MOD_PUBLIC_HDR})
    if(${CMAKE_CURRENT_SOURCE_DIR} IN_LIST _ALL_HDRS)
        # Current directory is already added
        return()
    elseif("." IN_LIST _ALL_HDRS)
        # Current directory is already added
        return()
    else()
        list(APPEND _MOD_PRIVATE_HDR ${CMAKE_CURRENT_SOURCE_DIR})
        set(_MOD_PRIVATE_HDR ${_MOD_PRIVATE_HDR} PARENT_SCOPE)
    endif ()
endfunction(_bcm_add_default_header_paths)

#======
# PRIVATE: Macro to create the public and private headers. We use the target_include_directories so the
# header files are transitive.
#
# @param TARGET_NAME    [in] Target name to add property to.
#======
macro(_bcm_add_module_headers TARGET_NAME)
    # Check if we need to add the current working directory on the default list.
    _bcm_add_default_header_paths()

    get_target_property(_TARGET_TYPE ${TARGET_NAME} TYPE)
    if("${_TARGET_TYPE}" STREQUAL "UTILITY")
        # Do nothing for custom targets
    elseif(NOT DEFINED _MOD_SRCS)
        if(DEFINED _MOD_PUBLIC_HDR)
            target_include_directories(${TARGET_NAME} INTERFACE ${_MOD_PUBLIC_HDR})
        endif()
    else ()
        if(DEFINED _MOD_PUBLIC_HDR)
            target_include_directories(${TARGET_NAME} PUBLIC ${_MOD_PUBLIC_HDR})
        endif()
        if(DEFINED _MOD_PRIVATE_HDR)
            target_include_directories(${TARGET_NAME} PRIVATE ${_MOD_PRIVATE_HDR})
        endif()
    endif()
endmacro(_bcm_add_module_headers)

#======
# PRIVATE: Macro to add the dependencies for the module. We use the target_link_libraries so the dependencies
# are transitive.
#
# @param TARGET_NAME    [in] Target name to add property to.
#======
macro(_bcm_add_module_dependencies TARGET_NAME)
    get_target_property(_TARGET_TYPE ${TARGET_NAME} TYPE)
    if("${_TARGET_TYPE}" STREQUAL "UTILITY")
        add_dependencies(${TARGET_NAME} ${_MOD_PUBLIC_DEPS} ${_MOD_PRIVATE_DEPS})
    elseif(NOT DEFINED _MOD_SRCS)
        if(DEFINED _MOD_PUBLIC_DEPS)
            target_link_libraries(${TARGET_NAME} INTERFACE ${_MOD_PUBLIC_DEPS})
        endif()
    else ()
        if(DEFINED _MOD_PUBLIC_DEPS)
            target_link_libraries(${TARGET_NAME} PUBLIC ${_MOD_PUBLIC_DEPS})
        endif()
        if(DEFINED _MOD_PRIVATE_DEPS)
            target_link_libraries(${TARGET_NAME} PRIVATE ${_MOD_PRIVATE_DEPS})
        endif()
        foreach(_FUNC ${_MOD_WRAPPED_FUNCS})
            target_link_libraries(${TARGET_NAME} PRIVATE "-Wl,--wrap=${_FUNC}")
        endforeach(_FUNC)
    endif()
endmacro(_bcm_add_module_dependencies)

#======
# PRIVATE: Macro to add the optional dependencies for the module. Since these may not be present, we don't
# add them with the target_link_libraries. In post-processing we will do this if the optional dependency
# is present as a valid target. The target properties, INTERFACE_OPTIONAL_PUBLIC_LIBRARIES,
# INTERFACE_OPTIONAL_PRIVATE_LIBRARIES and INTERFACE_OPTIONAL_INTERFACE_LIBRARIES are used to colocate this
# information with the target.
#
# @param TARGET_NAME    [in] Target name to add property to.
#======
macro(_bcm_add_module_optional_dependencies TARGET_NAME)
    get_target_property(_TARGET_TYPE ${TARGET_NAME} TYPE)
    if(NOT DEFINED _MOD_SRCS)
        if(DEFINED _MOD_PUBLIC_OPT_DEPS)
            set_target_properties(${TARGET_NAME} PROPERTIES
                                  INTERFACE_OPTIONAL_INTERFACE_LIBRARIES ${_MOD_PUBLIC_OPT_DEPS})
        endif()
    else ()
        if(DEFINED _MOD_PUBLIC_OPT_DEPS)
            set_target_properties(${TARGET_NAME} PROPERTIES
                                  INTERFACE_OPTIONAL_PUBLIC_LIBRARIES ${_MOD_PUBLIC_OPT_DEPS})
        endif()
        if(DEFINED _MOD_PRIVATE_OPT_DEPS)
            set_target_properties(${TARGET_NAME} PROPERTIES
                                  INTERFACE_OPTIONAL_PRIVATE_LIBRARIES ${_MOD_PRIVATE_OPT_DEPS})
        endif()
    endif()
endmacro(_bcm_add_module_optional_dependencies)

#======
# PRIVATE: Macro to add the system libraries to the INTERFACE_SYSTEM_LIBRARIES property so they can be
# added in post-processing at the end of the link. The global variable that collected these for the target
# is _MOD_SYSTEM_LIBS.
#
# @param TARGET_NAME    [in] Target name to add property to.
#======
macro(_bcm_add_module_system_libraries TARGET_NAME)
    if(DEFINED _MOD_SYSTEM_LIBS)
        set_target_properties(${TARGET_NAME} PROPERTIES
                              INTERFACE_SYSTEM_LIBRARIES "${_MOD_SYSTEM_LIBS}")
    endif()
endmacro(_bcm_add_module_system_libraries)

#======
# PRIVATE: Macro to add the cflags for the module. We use the target_compile_options so the cflags are
# transitive.
#
# @param TARGET_NAME    [in] Target name to add property to.
#======
macro(_bcm_add_module_cflags TARGET_NAME)
    if(NOT DEFINED _MOD_SRCS)
        if(_MOD_PUBLIC_CFLAGS)
            target_compile_options(${TARGET_NAME} INTERFACE ${_MOD_PUBLIC_CFLAGS})
            bcm_stringify_flags(_MY_LINKER_FLAGS ${_MOD_PUBLIC_CFLAGS})
            set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "${_MY_LINKER_FLAGS}")
        endif()
    else ()
        if(NOT "${DISABLE_EXTRA_WARNINGS}")
            if(BCM_EXTRA_C_WARNINGS)
                bcm_stringify_flags(BCM_WARNING_FLAGS ${BCM_EXTRA_C_WARNINGS})
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${BCM_WARNING_FLAGS}")
                bcm_string_remove_duplicates(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
            endif()
            if(BCM_EXTRA_CXX_WARNINGS)
                bcm_stringify_flags(BCM_WARNING_FLAGS ${BCM_EXTRA_CXX_WARNINGS})
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${BCM_WARNING_FLAGS}")
                bcm_string_remove_duplicates(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
            endif()
        endif()
        if(_MOD_PUBLIC_CFLAGS)
            target_compile_options(${TARGET_NAME} PUBLIC ${_MOD_PUBLIC_CFLAGS})
            bcm_stringify_flags(_MY_LINKER_FLAGS ${_MOD_PUBLIC_CFLAGS})
            set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "${_MY_LINKER_FLAGS}")
        endif()
        if(_MOD_PRIVATE_CFLAGS)
            # For private flags, we only apply them to C and CXX files
            unset(_C_SOURCE_FILES)
            foreach(_SRC ${_MOD_SRCS})
                get_source_file_property(_SRC_LANG ${_SRC} LANGUAGE)
                if("${_SRC_LANG}" STREQUAL "C" OR "${_SRC_LANG}" STREQUAL "CXX")
                    list(APPEND _C_SOURCE_FILES ${_SRC})
                 endif()
            endforeach(_SRC)

            bcm_stringify_flags(_MY_FLAGS ${_MOD_PRIVATE_CFLAGS})
            set_source_files_properties(${_C_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${_MY_FLAGS}")
            set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "${_MY_LINKER_FLAGS}")
        endif()
    endif()
endmacro(_bcm_add_module_cflags)

#======
# PRIVATE: Macro to add the definitions for the module. We use the target_compile_definitions so the
# definitions are transitive.
#
# @param TARGET_NAME    [in] Target name to add property to.
#======
macro(_bcm_add_module_defs TARGET_NAME)
    list(APPEND _MOD_PRIVATE_DEFS ${BCM_DEFINES})

    if(NOT DEFINED _MOD_SRCS)
        if(DEFINED _MOD_PUBLIC_DEFS)
            target_compile_definitions(${TARGET_NAME} INTERFACE ${_MOD_PUBLIC_DEFS})
        endif()
    else ()
        if(DEFINED _MOD_PUBLIC_DEFS)
            target_compile_definitions(${TARGET_NAME} PUBLIC ${_MOD_PUBLIC_DEFS})
        endif()
        if(DEFINED _MOD_PRIVATE_DEFS)
            target_compile_definitions(${TARGET_NAME} PRIVATE ${_MOD_PRIVATE_DEFS})
        endif()
    endif()
endmacro(_bcm_add_module_defs)

#======
# PRIVATE: Macro to check that the required variables are set
# @param ARGN           [in] List of variables that are required for the target
#======
macro(_bcm_check_mandatory_variables)
    foreach(_MY_MANVAR ${ARGN})
        if(NOT DEFINED ${_MY_MANVAR})
            file(RELATIVE_PATH _RELATIVE_SOURCE_DIR ${SOURCE_TOP} ${CMAKE_CURRENT_SOURCE_DIR})
            message(FATAL_ERROR "${MSG_PREAMBLE} Must define [${ARGN}] in ${_RELATIVE_SOURCE_DIR}/CMakeLists.txt")
        endif()
    endforeach(_MY_MANVAR)
endmacro(_bcm_check_mandatory_variables)

#======
# PRIVATE: Macro to check that the PUBLIC/PRIVATE setting was passed in
# @param VIS            [in] Visibility value
# @param TYPE           [in] Who is doing the validation
#======
macro(_bcm_check_visibility_variable VIS TYPE)
    if(NOT (("${VIS}" STREQUAL "PUBLIC") OR ("${VIS}" STREQUAL "PRIVATE")))
        message(FATAL_ERROR "${MSG_PREAMBLE} Target=${_MOD_NAME} ${TYPE} requires 'PUBLIC' or 'PRIVATE' visibility. Given: '${VIS}'")
    endif()
endmacro(_bcm_check_visibility_variable)

#======
# PRIVATE: Macro to determine if a flag is set in the parameters to a bcm_create_*_target() macro. We simply
# look in the list for the given varialble and return TRUE or FALSE depending on if it exists. If the option
# is 'STRIP', we only allow that for the host.
#
# @param ARG_SET        [out] TRUE - argument exists / FALSE - argument does not exist
# @param ARG_FLAG       [in] Flag we are looking for in the argument list
# @param ARGN           [in] list of arguments given to the bcm_create_*_target() macro
#======
macro(_bcm_param_exists ARG_SET ARG_FLAG)
    set(_ARG_LIST ${ARGN})

    if(("${ARG_FLAG}" STREQUAL "STRIP") AND (("${SUBSYSTEM}" STREQUAL "embedded") OR IGNORE_STRIP))
        # Not allowed for embedded and If told to ignore the strip directive (the user wants the unstripped result).
        set(${ARG_SET} FALSE)
    else()
        if(${ARG_FLAG} IN_LIST _ARG_LIST)
            set(${ARG_SET} TRUE)
        else()
            set(${ARG_SET} FALSE)
        endif()
    endif()
endmacro(_bcm_param_exists)

#======
# PRIVATE: Determine the install directory to use (if any) for the bcm_create_*_target() macro. If the EXPORT
# is set, it means we use the pre-defined install directories (bin, lib). If EXPORT is not set, we look for
# anything left once we've gone through all the possible parameters.
#
# @param INSTALL_DIR    [out] Filepath to an install dir, will be ignored if EXPORT was set
# @param ARGN
#======
macro(_bcm_find_install_dir INSTALL_DIR)
    # Define the list of possible arguments
    set(_POSSIBLE_ARGS      EXPORT NO_RESET INTERNAL STRIP RELEASE)

    unset(${INSTALL_DIR})
    set(_LOCAL_LIST ${ARGN})
    _bcm_param_exists(_HAS_EXPORT EXPORT ${ARGN})

    if(DEFINED _LOCAL_LIST)
        if(NOT ${_HAS_EXPORT})
            # Not an export so look for the install directory if it exists. Start by removing the known
            # parameters we can have from the argument list. The remainder would be the install dir
            list(REMOVE_ITEM _LOCAL_LIST ${_POSSIBLE_ARGS})
            list(LENGTH _LOCAL_LIST _LOCAL_LIST_LEN)

            if(${_LOCAL_LIST_LEN} EQUAL 1)
                set(${INSTALL_DIR} ${_LOCAL_LIST})
            elseif(${_LOCAL_LIST_LEN} GREATER 1)
                bcm_message(FATAL_ERROR "More than one install directory given: ${_LOCAL_LIST}")
            endif()
        endif()
    endif()
endmacro(_bcm_find_install_dir)

#======
# PRIVATE: Macro to strip the symbols from a shared library or executable and save them as debug symbols
#
# @param TARGET         [in] Target we are stripping the symbols from
#======
macro(_bcm_strip_symbols TARGET)
    set(_STRIP_OUTPUT_DIR strip)
    if("${SUBSYSTEM}" STREQUAL "host")
        add_custom_command(TARGET ${TARGET}
                           POST_BUILD
                           COMMAND mkdir -p ${_STRIP_OUTPUT_DIR}
                           COMMAND ${BCM_OBJCOPY} --strip-debug --strip-unneeded $<TARGET_FILE:${TARGET}>
                                   ${_STRIP_OUTPUT_DIR}/$<TARGET_FILE_NAME:${TARGET}>
                           COMMAND ${BCM_OBJCOPY} --only-keep-debug $<TARGET_FILE:${TARGET}>
                                   ${_STRIP_OUTPUT_DIR}/${TARGET}.debug_symbols
                           COMMAND ${BCM_OBJCOPY} --add-gnu-debuglink=${_STRIP_OUTPUT_DIR}/${TARGET}.debug_symbols
                                   ${_STRIP_OUTPUT_DIR}/$<TARGET_FILE_NAME:${TARGET}>
                           COMMAND tar -czf ${_STRIP_OUTPUT_DIR}/${TARGET}.debug_symbols.tar.gz
                                   -C ${_STRIP_OUTPUT_DIR} ${TARGET}.debug_symbols
                           COMMENT "Stripping symbols from ${TARGET}")
    endif()
endmacro(_bcm_strip_symbols)

#======
# PRIVATE: Macro to create the install steps for stripped targets. This must be called after the targets
# 'install' rule.
#
# @param TARGET         [in] Target we are stripping the symbols from
# @param INSTALL_DIR    [in] Install directory for the target
#======
macro(_bcm_strip_install TARGET INSTALL_DIR)
    set(_STRIP_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/strip)
    if("${SUBSYSTEM}" STREQUAL "host")
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/strip/$<TARGET_FILE_NAME:${TARGET}> DESTINATION ${INSTALL_DIR})
        if(BCM_INSTALL_STRIP_SYMBOLS)
            install(FILES ${CMAKE_CURRENT_BINARY_DIR}/strip/${TARGET}.debug_symbols.tar.gz DESTINATION ${INSTALL_DIR})
        endif(BCM_INSTALL_STRIP_SYMBOLS)
    endif()
endmacro(_bcm_strip_install)

#======
# PRIVATE: Macro to set the install rule if one is appropriate. Called by the App and Linux Module create macros.
# The given directory is relative to CMAKE_INSTALL_PREFIX defined in the top level CMakeLists.txt file. We also
# propagate the relative directory up so we can create a 'clean' for it. Use the cache for the propagation
# (variable BCM_INSTALL_DIRS).
# @param OUT_STR        [out] What status to display for CMake log
# @param TARGET         [in] Target to add the install rule for
# @param EXPORT         [in] Boolean indicating if the target is to be exported
# @param INSTALL_DIR    [in] If not to be exported, this optionally can have an install directory
# @param STRIP          [in] Install the stripped version
#======
macro(_bcm_install_target OUT_STR TARGET EXPORT INSTALL_DIR STRIP)
    unset(${OUT_STR})
    unset(_ADDED_INSTALL_RULE)

    if(${EXPORT})
        # To be exported so use the defined install directories for the target and generated CMake files
        # This is only supported for targets so we don't need to check that.
        # If both RUNTIME_OUTPUT_DIRECTORY and RUNTIME_OUTPUT_NAME are set - install specific file
        bcm_get_target_property(_TARGET_OUT_DIR ${TARGET} RUNTIME_OUTPUT_DIRECTORY)
        bcm_get_target_property(_TARGET_OUT_NAME ${TARGET} RUNTIME_OUTPUT_NAME)
        bcm_get_target_property(_TARGET_TYPE ${TARGET} TYPE)

        if(NOT DEFINED _TARGET_OUT_DIR OR NOT DEFINED _TARGET_OUT_NAME)
            if("${_TARGET_TYPE}" STREQUAL "EXECUTABLE")
                set(_INSTALL_DIR bin)
            else()
                set(_INSTALL_DIR lib)
            endif()

            if(DEFINED _MOD_PUBLIC_HDR)
                # There are public headers we need to export. For that, we need them in the build tree.
                # Here we determine if they are in the build tree or not. If they are in the source tree,
                # we link the directory to the "install tree", under 'include' and update the header
                # information. If they are in the build tree, we leave them.
                unset(_MY_MOD_PUBLIC_HDR)

                foreach(_HDR ${_MOD_PUBLIC_HDR})
                    if("${_HDR}" MATCHES "${BUILD_TOP}")
                        # We can keep the path we have
                        list(APPEND _MY_MOD_PUBLIC_HDR ${_HDR})
                    else()
                        # The directory is in the source tree, so we need to make sure it shows up
                        # in the install tree.
                        if(IS_ABSOLUTE  ${_HDR})
                            set(_ABSOLUTE_HDR ${_HDR})
                        else()
                            set(_ABSOLUTE_HDR ${CMAKE_CURRENT_SOURCE_DIR}/${_HDR})
                        endif()
                        file(RELATIVE_PATH _RELATIVE_HDR ${SOURCE_TOP} ${_ABSOLUTE_HDR})
                        file(GLOB _MY_HEADERS LIST_DIRECTORIES false RELATIVE ${SOURCE_TOP} ${_ABSOLUTE_HDR}/*.h)

                        # Link the headers in to the install tree.
                        foreach(_MY_HEADER ${_MY_HEADERS})
                            get_filename_component(_DIRNAME ${_MY_HEADER} DIRECTORY)
                            execute_process(COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/include/${_DIRNAME})
                            execute_process(COMMAND ln -sf ${SOURCE_TOP}/${_MY_HEADER}
                                                           ${CMAKE_INSTALL_PREFIX}/include/${_MY_HEADER})
                        endforeach(_MY_HEADER)

                        # Add the header path from the install directory
                        list(APPEND _MY_MOD_PUBLIC_HDR $<INSTALL_INTERFACE:${_RELATIEVE_HDR}>)
                    endif()
                endforeach(_HDR)

                # Update the public headers for later target properties
                set(_MOD_PUBLIC_HDR ${_MY_MOD_PUBLIC_HDR})
            endif()

            if(IS_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
                install(TARGETS ${TARGET} DESTINATION ${_INSTALL_DIR} EXPORT ${TARGET} INCLUDES DESTINATION include)
            else()
                if(${STRIP})
                    # Add additional install steps for using the stripped version of files
                    _bcm_strip_install(${TARGET} ${_INSTALL_DIR})
                else()
                    install(TARGETS ${TARGET} DESTINATION ${_INSTALL_DIR} EXPORT ${TARGET})
                endif()
            endif()
            install(EXPORT ${TARGET} DESTINATION target-modules)
            set(_ADDED_INSTALL_RULE TRUE)
        endif()
    elseif(DEFINED ${INSTALL_DIR})
        set(_INSTALL_DIR ${${INSTALL_DIR}})

        if(TARGET ${TARGET})
            # If both RUNTIME_OUTPUT_DIRECTORY and RUNTIME_OUTPUT_NAME are set - install specific file
            bcm_get_target_property(_TARGET_OUT_DIR ${TARGET} RUNTIME_OUTPUT_DIRECTORY)
            bcm_get_target_property(_TARGET_OUT_NAME ${TARGET} RUNTIME_OUTPUT_NAME)

            if(NOT DEFINED _TARGET_OUT_DIR OR NOT DEFINED _TARGET_OUT_NAME)
                if(${STRIP})
                    # Add additional install steps for using the stripped version of files
                    _bcm_strip_install(${TARGET} ${_INSTALL_DIR})
                else()
                    install(TARGETS ${TARGET} DESTINATION ${_INSTALL_DIR})
                endif()
            else()
                install(FILES ${_TARGET_OUT_DIR}/${_TARGET_OUT_NAME} DESTINATION ${_INSTALL_DIR})
            endif()
        else()
            install(FILES ${TARGET} DESTINATION ${_INSTALL_DIR})
        endif()
        set(_ADDED_INSTALL_RULE TRUE)
    endif()

    if(${_ADDED_INSTALL_RULE})
        # Add the directory to the list in the cache, but don't store duplicates
        list(APPEND BCM_INSTALL_DIRS ${_INSTALL_DIR})
        list(REMOVE_DUPLICATES BCM_INSTALL_DIRS)
        set(BCM_INSTALL_DIRS ${BCM_INSTALL_DIRS} CACHE STRING "List of Install Directories" FORCE)

        set(${OUT_STR} ", install dir '${_INSTALL_DIR}'")
    endif()
endmacro(_bcm_install_target)

#======
# PRIVATE: Macro to clear all the lists. Called after the build targets have been added
#======
macro(_bcm_module_globals_clear)
    unset(_MOD_SRCS)
    unset(_MOD_PUBLIC_HDR)
    unset(_MOD_PRIVATE_HDR)
    unset(_MOD_PUBLIC_DEPS)
    unset(_MOD_PRIVATE_DEPS)
    unset(_MOD_PUBLIC_OPT_DEPS)
    unset(_MOD_PRIVATE_OPT_DEPS)
    unset(_MOD_SYSTEM_LIBS)
    unset(_MOD_PUBLIC_CFLAGS)
    unset(_MOD_PRIVATE_CFLAGS)
    unset(_MOD_PUBLIC_DEFS)
    unset(_MOD_PRIVATE_DEFS)
    unset(_MOD_CODEGEN_OUTPUT)
    unset(_MOD_WRAPPED_FUNCS)
endmacro(_bcm_module_globals_clear)

#======
# PRIVATE: Macro to add all the target specific stuff. Done after the target is defined. By default, these
# are set for _MOD_NAME, but an optional alternative target can be given. The alternate is used when adding
# the kernel module targets for libraries.
#
# @param ARGN           [in] Optional alternate target, default is the _MOD_NAME global
#======
macro(_bcm_module_add_target_specifics)
    set(_OPTIONAL_MOD_NAME ${ARGN})

    if(DEFINED _OPTIONAL_MOD_NAME)
        set(_TARGET_NAME ${_OPTIONAL_MOD_NAME})
    else()
        set(_TARGET_NAME ${_MOD_NAME})
    endif()

    _bcm_add_module_headers(${_TARGET_NAME})
    _bcm_add_module_dependencies(${_TARGET_NAME})
    _bcm_add_module_optional_dependencies(${_TARGET_NAME})
    _bcm_add_module_system_libraries(${_TARGET_NAME})
    _bcm_add_module_cflags(${_TARGET_NAME})
    _bcm_add_module_defs(${_TARGET_NAME})
endmacro(_bcm_module_add_target_specifics)

#======
# PRIVATE: Create an interface libary for the given module name. This is used for both the
# ${_MOD_NAME}_${_HEADER_ONLY_EXT} that can be used in place of hard-coded include paths and for Linux kernel
# module dependencies.
#
# @param LIB_NAME           [in] What to name the library (e.g. ${_MOD_NAME}_${_HEADER_ONLY_EXT})
# @param EXTENSION          [in] Extention to add to the target names
#======
function(_bcm_create_interface_lib LIB_NAME EXTENSION)
    add_library(${LIB_NAME} INTERFACE)

    # Clear the sources, get the proper dependencies and add headers/dependencies
    unset(_MOD_SRCS)
    string(REGEX REPLACE "([^;]+)" "\\1_${EXTENSION}" _MOD_PUBLIC_DEPS  "${_MOD_PUBLIC_DEPS}")

    # Make sure we restore any _HEADER_ONLY_EXT dependencies in the list (the regex would duplicate the extension)
    string(REPLACE "_${EXTENSION}_${EXTENSION}" "_${EXTENSION}" _MOD_PUBLIC_DEPS "${_MOD_PUBLIC_DEPS}")

    _bcm_add_module_headers(${LIB_NAME})
    _bcm_add_module_dependencies(${LIB_NAME})
    _bcm_add_module_defs(${LIB_NAME})

    # If there is a corresponding codegen target, add a dependency on it for the kernel lib version as well.
    # (this is useful for interface libraries, which normally build nothing).
    if(DEFINED _MOD_CODEGEN_OUTPUT)
        add_dependencies(${LIB_NAME} ${_MOD_NAME}_codegen)
    endif()
endfunction(_bcm_create_interface_lib)

#======
# PRIVATE: Add a rule to install the binary in the release tree. We first check that the underlying macro exists
# since it won't in the release_tree.
#
# @param BINARY_NAME        [in] Name of the binary we want in the release tree
#======
macro(_bcm_release_binary BINARY_NAME)
    if(COMMAND bcm_release_install_binary)
        bcm_release_install_binary(${BINARY_NAME})
    endif()
endmacro(_bcm_release_binary)

#======
# PRIVATE: Add a per-module global to the cache
#
# @param CACHE_VAR          [in] CMake cache variable name to update
# @param CACHE_DESC         [in] Description to use for CMake cache entry
# @param ARGN               [in] What to add to the CMake cache entry
#======
function(_bcm_add_to_global_cache_var CACHE_VAR CACHE_DESC)
    if(ARGN)
        list(APPEND ${CACHE_VAR} ${ARGN})
        list(REMOVE_DUPLICATES ${CACHE_VAR})
        set(${CACHE_VAR} ${${CACHE_VAR}} CACHE STRING "${CACHE_DESC}" FORCE)
    endif()
endfunction(_bcm_add_to_global_cache_var)

#======
# Set the Aspen module name. The macro sets the global variable _MOD_NAME. Equivalent to the Make 'MOD_NAME'.
#
# @param MOD_NAME       [in] Name of the module to build
#======
macro(bcm_module_name MOD_NAME)
    set(_MOD_NAME ${MOD_NAME})
    set(${_MOD_NAME}_EXISTS y CACHE BOOL "${_MOD_NAME} Exists" FORCE)
    set(${_MOD_NAME}_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE FILEPATH "${_MOD_NAME} Source Directory" FORCE)
    set(${_MOD_NAME}_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE FILEPATH "${_MOD_NAME} Build Directory" FORCE)
    set(${_MOD_NAME}_PUBLIC_DEPS ${_MOD_PUBLIC_DEPS} CACHE STRING "${_MOD_NAME} Public Dependencies" FORCE)
    set(${_MOD_NAME}_PRIVATE_DEPS ${_MOD_PRIVATE_DEPS} CACHE STRING "${_MOD_NAME} Private Dependencies" FORCE)
    set(${_MOD_NAME}_PUBLIC_DEFS ${_MOD_PUBLIC_DEFS} CACHE STRING "${_MOD_NAME} Public Definitions" FORCE)
    set(${_MOD_NAME}_PRIVATE_DEFS ${_MOD_PRIVATE_DEFS} CACHE STRING "${_MOD_NAME} Private Definitions" FORCE)

    # Make sure we start with the default C/CXX flags
    bcm_stringify_flags(CMAKE_C_FLAGS ${BCM_CFLAGS})
    bcm_stringify_flags(CMAKE_CXX_FLAGS ${BCM_CXXFLAGS})
endmacro(bcm_module_name)

#======
# Set the module sources. The source files can be C, C++ or Assembly files. The macro appends the source
# to a global list, _MOD_SRCS, which is then used in rule creation. This macro can be called multiple times
# in a CMakeLists.txt file with additional source files. Equivalent to the Make 'srcs'. If called with 'RESET',
# this will unset the global variable. The RESET can be used when a single CMakeLists.txt file has multiple
# targets.
#
# @param ARGN           [in] Sources to append to the running list (could be 'RESET' as well)
#======
macro(bcm_module_srcs)
    if("${ARGV0}" STREQUAL "RESET")
        unset(_MOD_SRCS)
    else()
        # All source files get added to the global
        list(APPEND _MOD_SRCS ${ARGN})
    endif()
endmacro(bcm_module_srcs)

#======
# Set the header paths to include. These can be public (included for libraries that have a dependency on
# this one) or private (only available for this library). The paths do not include the -I. The macro appends
# the paths to a global list, _MOD_PUBLIC_HDR or _MOD_PRIVATE_HDR, which are then used in rule creation.
# This macro can be called multiple times in a CMakeLists.txt file with additional paths. Equivalent to the
# Make 'MOD_INC_DIRS' when used with PUBLIC and the Make 'EXTRA_INCLUDES' when used with PRIVATE. If called
# with 'RESET', this will unset the global variable. The RESET can be used when a single CMakeLists.txt file
# has multiple targets.
#
# @param VIS            [in] Indicate visibility of the headers <PUBLIC|PRIVATE> (or RESET to clear global)
# @param ARGN           [in] Relative path to directories containing public header files
#======
macro(bcm_module_header_paths VIS)
    if("${VIS}" STREQUAL "RESET")
        unset(_MOD_PUBLIC_HDR)
        unset(_MOD_PRIVATE_HDR)
    else()
        _bcm_check_visibility_variable(${VIS} "bcm_module_header_paths")
        list(APPEND _MOD_${VIS}_HDR ${ARGN})
        list(REMOVE_DUPLICATES _MOD_${VIS}_HDR)
    endif()
endmacro(bcm_module_header_paths)

#======
# Add target dependencies. These can be public (included for libraries that have a dependency on this one)
# or private (only available for this library). The macro appends the dependencies to a global list,
# _MOD_PUBLIC_DEPS or _MOD_PRIVATE_DEPS, which are then used in rule creation. This macro can be called
# multiple times in a CMakeLists.txt file with additional dependencies. Equivalent to the Make 'MOD_DEPS'
# when used with PUBLIC. If called with 'RESET', this will unset the global variable. The RESET can be
# used when a single CMakeLists.txt file has multiple targets.
#
# @param VIS            [in] Indicate visibility of the headers <PUBLIC|PRIVATE> (or RESET to clear global)
# @param ARGN           [in] Modules this one is dependant on.
#======
macro(bcm_module_dependencies VIS)
    if("${VIS}" STREQUAL "RESET")
        unset(_MOD_PUBLIC_DEPS)
        unset(_MOD_PRIVATE_DEPS)
    else()
        _bcm_check_visibility_variable(${VIS} "bcm_module_dependencies")
        list(APPEND _MOD_${VIS}_DEPS ${ARGN})
        list(REMOVE_DUPLICATES _MOD_${VIS}_DEPS)

        # Add to per-module global list
        _bcm_add_to_global_cache_var(${_MOD_NAME}_${VIS}_DEPS "${_MOD_NAME} ${VIS} Dependencies" ${ARGN})
    endif()
endmacro(bcm_module_dependencies)

#======
# Add target optional dependencies. These can be public (included for libraries that have a dependency on this one)
# or private (only available for this library). The macro appends the dependencies to a global list,
# _MOD_PUBLIC_OPT_DEPS or _MOD_PRIVATE_OPT_DEPS, which are then used in rule creation. This macro can be called
# multiple times in a CMakeLists.txt file with additional dependencies. If called with 'RESET', this will
# unset the global variable. The RESET can be used when a single CMakeLists.txt file has multiple targets.
#
# @param VIS            [in] Indicate visibility of the headers <PUBLIC|PRIVATE> (or RESET to clear global)
# @param ARGN           [in] Modules this one is dependant on.
#======
macro(bcm_module_optional_dependencies VIS)
    if("${VIS}" STREQUAL "RESET")
        unset(_MOD_PUBLIC_OPT_DEPS)
        unset(_MOD_PRIVATE_OPT_DEPS)
    else()
        _bcm_check_visibility_variable(${VIS} "bcm_module_optional_dependencies")
        list(APPEND _MOD_${VIS}_OPT_DEPS ${ARGN})
        list(REMOVE_DUPLICATES _MOD_${VIS}_OPT_DEPS)
    endif()
endmacro(bcm_module_optional_dependencies)

#======
# Add target kernel dependencies. These can be public (included for libraries that have a dependency on this one)
# or private (only available for this library). The macro appends the dependencies to a global list,
# _MOD_PUBLIC_DEPS or _MOD_PRIVATE_DEPS, which are then used in rule creation. This macro can be called
# multiple times in a CMakeLists.txt file with additional dependencies. Equivalent to the Make 'MOD_DEPS'
# when used with PUBLIC.
#
# The kernel specific part of these is the appending of '_kernel' to the dependency names as this tells the
# kernel module build to pull in the source or Module.symvers for the linux libs and modules, respectively.
# This is always added as a private dependency.
#
# If the visibility is PUBLIC, then we also add the targets to the normal dependencies so they are available to
# those with a dependency on this module. Note that these would be header-only depenencies.
#
# @param VIS            [in] Indicate visibility of the headers <PUBLIC|PRIVATE>
# @param ARGN           [in] Modules this one is dependant on.
#======
macro(bcm_module_kernel_dependencies VIS)
    _bcm_check_visibility_variable(${VIS} "bcm_module_kernel_dependencies")
    set(_MY_DEPS_IN ${ARGN})
    unset(_MY_PRIVATE_DEPS)
    unset(_MY_PUBLIC_DEPS)

    # Append the '_kernel' to all the dependencies given to indicate they are part of a module build
    string(REGEX REPLACE "([^;]+)" "\\1_${_KERNEL_EXT}" _MY_PRIVATE_DEPS "${_MY_DEPS_IN}")

    # If VIS == PUBLIC, we want the header-only versions (name without '_kernel') on the dependency list
    if("${VIS}" STREQUAL "PUBLIC")
        list(APPEND _MY_PUBLIC_DEPS ${_MY_DEPS_IN})
    endif()

    # Now add to the globals
    list(APPEND _MOD_PRIVATE_DEPS ${_MY_PRIVATE_DEPS})
    list(REMOVE_DUPLICATES _MOD_PRIVATE_DEPS)

    if(_MY_PUBLIC_DEPS)
        list(APPEND _MOD_PUBLIC_DEPS ${_MY_PUBLIC_DEPS})
        list(REMOVE_DUPLICATES _MOD_PUBLIC_DEPS)
    endif()

    # Add to per-module global list
    _bcm_add_to_global_cache_var(${_MOD_NAME}_PRIVATE_DEPS "${_MOD_NAME} PRIVATE Dependencies" ${_MY_PRIVATE_DEPS})
    _bcm_add_to_global_cache_var(${_MOD_NAME}_PUBLIC_DEPS "${_MOD_NAME} PUBLIC Dependencies" ${_MY_PUBLIC_DEPS})
endmacro(bcm_module_kernel_dependencies)

#======
# Add target system libraries: The system libraries are always considered public and are stored in
# _MOD_SYSTEM_LIBS. A system library is any library that you don't want to be part of a -Wl,--start-group/
# --end-group. The system libraries will come at the end of the link command.
#
# @param ARGN           [in] system libraries (no '-l'). Could also be 'RESET'
#======
macro(bcm_module_system_libraries)
    if(${ARGC} GREATER 0)
        if("${ARGV0}" STREQUAL "RESET")
            unset(_MOD_SYSTEM_LIBS)
        elseif("${ARGV0}" STREQUAL "PUBLIC" OR "${ARGV0}" STREQUAL "PRIVATE")
            bcm_message(FATAL_ERROR "System library setting invalid parameter '${ARGV0}'")
        else()
            list(APPEND _MOD_SYSTEM_LIBS ${ARGN})
            list(REMOVE_DUPLICATES _MOD_SYSTEM_LIBS)
        endif()
    endif()
endmacro(bcm_module_system_libraries)

#======
# Set the compile options to use beyond the default. This does not include the -D definitions as they are
# handled by bcm_module_definitions() macro. These can be public (included for libraries that have a
# dependency on this one) or private (only available for this library). The macro appends the cflags to
# a global list, _MOD_PUBLIC_CFLAGS or _MOD_PRIVATE_CFLAGS, which are then used in rule creation. This
# macro can be called multiple times in a CMakeLists.txt file with additional compile flags. Equivalent
# to the Make 'EXTRA_CFLAGS' when used with PRIVATE. If called with 'RESET', this will unset the global
# variable. The RESET can be used when a single CMakeLists.txt file has multiple targets.
#
# @param VIS            [in] Indicate visibility of the headers <PUBLIC|PRIVATE> (or RESET to clear global)
# @param ARGN           [in] Compile flags for this module.
#======
macro(bcm_module_cflags VIS)
    if("${VIS}" STREQUAL "RESET")
        unset(_MOD_PUBLIC_CFLAGS)
        unset(_MOD_PRIVATE_CFLAGS)
    else()
        _bcm_check_visibility_variable(${VIS} "bcm_module_cflags")
        list(APPEND _MOD_${VIS}_CFLAGS ${ARGN})
        list(REMOVE_DUPLICATES _MOD_${VIS}_CFLAGS)
    endif()
endmacro(bcm_module_cflags)

#======
# Set the -D options for the module and must include the '-D'. These can be public (included for libraries
# that have a dependency on this one) or private (only available for this library). The macro appends the
# definitions to a global list, _MOD_PUBLIC_DEFS or _MOD_PRIVATE_DEFS, which are then used in rule creation.
# This macro can be called multiple times in a CMakeLists.txt file with additional definitions. Equivalent
# to the Make 'MOD_DEFS' when used with PUBLIC. If called with 'RESET', this will unset the global variable.
# The RESET can be used when a single CMakeLists.txt file has multiple targets.
#
# @param VIS            [in] Indicate visibility of the headers <PUBLIC|PRIVATE> (or RESET to clear global)
# @param ARGN           [in] Compile flags for this module.
#======
macro(bcm_module_definitions VIS)
    if("${VIS}" STREQUAL "RESET")
        unset(_MOD_PUBLIC_DEFS)
        unset(_MOD_PRIVATE_DEFS)
    else()
        _bcm_check_visibility_variable(${VIS} "bcm_module_definitions")
        list(APPEND _MOD_${VIS}_DEFS ${ARGN})
        list(REMOVE_DUPLICATES _MOD_${VIS}_DEFS)

        # Add to per-module global list
        _bcm_add_to_global_cache_var(${_MOD_NAME}_${VIS}_DEFS "${_MOD_NAME} ${VIS} Definitions" ${ARGN})

        # Add to the global list
        _bcm_add_to_global_cache_var(BCM_GLOBAL_DEFINITIONS "Broadcom Global Definitions" ${ARGN})
    endif()
endmacro(bcm_module_definitions)

#======
# Add the code generation output for the module. The macro sets the global, _MOD_CODEGEN_OUTPUT.
# This is called from cmake/modules/codegen_macros.cmake to set a target for the generated .c/.h
# files.
#
# @param ARGN           [in] Compile flags for this module.
#======
macro(bcm_module_codegen_output)
    list(APPEND _MOD_CODEGEN_OUTPUT ${ARGN})
    list(REMOVE_DUPLICATES _MOD_CODEGEN_OUTPUT)
endmacro(bcm_module_codegen_output)

#====
# Create a wrap function for the linker using the GCC "--wrap" functionality.
# The modifications to the linker flags will apply to any executable that depends on the current module.
#
# @param ARGV           [in] list of functions to wrap
#====
macro(bcm_module_function_overrides)
    list(APPEND _MOD_WRAPPED_FUNCS ${ARGN})
endmacro(bcm_module_function_overrides)

#====
# Batch compilation support
#====
bcm_make_debug_option(BATCH_COMPILE BOOL "Batch compilation (multiple files in a single compiler invocation)" n)

#======
# Clear batch compilation artifacts if any
#======
macro(batch_compile_clear)
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/.${_MOD_NAME}.compile.files)
endmacro(batch_compile_clear)

#======
# Set batch compilation properties
#======
macro(batch_compile_prepare)
    if(BATCH_COMPILE AND NOT ${_MOD_NAME}_disable_batch_compile)
        # Remove stale batch compilation info if any
        batch_compile_clear()
        # Compile in batch(es) just before link
        set_property(TARGET ${_MOD_NAME} PROPERTY C_COMPILER_LAUNCHER
            ${SOURCE_TOP}/cmake/scripts/batch_compile_cache.sh ${_MOD_NAME} ${CMAKE_C_COMPILER_LAUNCHER})
        set_property(TARGET ${_MOD_NAME} PROPERTY CXX_COMPILER_LAUNCHER
            ${SOURCE_TOP}/cmake/scripts/batch_compile_cache.sh ${_MOD_NAME} ${CMAKE_CXX_COMPILER_LAUNCHER})
        set_property(TARGET ${_MOD_NAME} PROPERTY RULE_LAUNCH_LINK
            "${SOURCE_TOP}/cmake/scripts/batch_compile_execute.sh ${_MOD_NAME}")
    endif()
endmacro(batch_compile_prepare)

#======
# Create the library target from the globals set. _MOD_NAME is required. For Linux module builds we want
# to include the headers and dependencies from a regular library, but not the CFLAGS, definitions or build
# rules. To handle this we create a second, parallel, interface library target for the Linux modules and
# libraries to use. Since we also call in to this macro from the Linux module and library builds, an optional
# parameter is provided that skips thee clearing of the global variables. It is up to the caller to do the clear
# when this parameter is used.
#
# @param ARGN           [in] Optional parameters as:
#                               - NO_RESET with any other options (Don't clear the global variables)
#                               - INTERNAL used to control logging
#                               - EXPORT (indicates whether to export the library or not)
#======
macro(bcm_create_lib_target)
    _bcm_check_mandatory_variables(_MOD_NAME)
    _bcm_param_exists(_NO_RESET NO_RESET ${ARGN})
    _bcm_param_exists(_EXPORT EXPORT ${ARGN})
    _bcm_param_exists(_INTERNAL INTERNAL ${ARGN})
    unset(_INSTALL_DIR)

    # Store information that module is a library in the cache for other modules to see
    set(${_MOD_NAME}_TYPE lib CACHE STRING "${_MOD_NAME} type" FORCE)

    if(NOT DEFINED _MOD_SRCS)
        # An interface library is one that has no source files, only headers. We use this of no source
        # files are given.
        add_library(${_MOD_NAME} INTERFACE)
    else()
        # If we have source files, this is treated as a static library.
        add_library(${_MOD_NAME} STATIC ${_MOD_SRCS})
        # Add library to global list
        list(APPEND BCM_ALL_LIB_MODULES ${_MOD_NAME})
        set(BCM_ALL_LIB_MODULES ${BCM_ALL_LIB_MODULES} CACHE STRING "All Library Modules" FORCE)
        # Prepare for batch compilation if necessary
        batch_compile_prepare()

        # Set the install target if the macro was passed one.
        _bcm_install_target(_OUT_STR ${_MOD_NAME} ${_EXPORT} _INSTALL_DIR FALSE)
    endif()

    # Add in the transitive properties to the library target
    _bcm_module_add_target_specifics()

    # If there is a corresponding codegen target, add a dependency on it
    # (this is useful for interface libraries, which normally build nothing).
    if(DEFINED _MOD_CODEGEN_OUTPUT)
        add_custom_target(${_MOD_NAME}_codegen DEPENDS ${_MOD_CODEGEN_OUTPUT})
        add_dependencies(${_MOD_NAME} ${_MOD_NAME}_codegen)
    endif()

    # Add an interface libary with the name, ${_MOD_NAME}_${_HEADER_ONLY_EXT}, that can be used as a dependency
    # in place of hardcoded header paths. We want to include the definitions with this as well.
    _bcm_create_interface_lib(${_MOD_NAME}_${_HEADER_ONLY_EXT} ${_HEADER_ONLY_EXT})

    # Clear the variables only if not told to keep them
    if(NOT ${_INTERNAL})
        if(NOT ${_NO_RESET})
            _bcm_module_globals_clear()
        endif()
        bcm_message(STATUS "Added 'lib' rules for '${_MOD_NAME}'")
    endif()
endmacro(bcm_create_lib_target)

#======
# Create the shared library target from the globals set. _MOD_NAME are required. The
# shared library can be used on linux systems and its primary use case is BAL/SDN Agent.
#
# @param ARGN           [in] Optional parameters as:
#                               - NO_RESET with any other options (Don't clear the global variables)
#                               - EXPORT (indicates whether to export the library or not)
#                               - STRIP (indicates that we should strip the symbols)
#                               - RELEASE (indicates that the resulting binary goes in host_driver_images
#                               - <install dir>  or EXPORT (indicates whether to export or put in install dir)
#======
macro(bcm_create_shared_lib_target)
    _bcm_check_mandatory_variables(_MOD_NAME)
    _bcm_param_exists(_NO_RESET NO_RESET ${ARGN})
    _bcm_param_exists(_EXPORT EXPORT ${ARGN})
    _bcm_param_exists(_STRIP STRIP ${ARGN})
    _bcm_param_exists(_RELEASE RELEASE ${ARGN})
    _bcm_find_install_dir(_INSTALL_DIR ${ARGN})

    # Store information that module is a shared library in the cache for other modules to see
    set(${_MOD_NAME}_TYPE shared_lib CACHE STRING "${_MOD_NAME} type" FORCE)

    # Add the library as shared or interface depending on the sources
    if(NOT DEFINED _MOD_SRCS)
        add_library(${_MOD_NAME} INTERFACE)
    else()
        bcm_add_system_libraries_to_link(${_MOD_NAME}_SYSTEM_LIBRARIES SHARED_LIBRARY)
        add_library(${_MOD_NAME} SHARED ${_MOD_SRCS})
        # Prepare for batch compilation if necessary
        batch_compile_prepare()
    endif()

    # Determine if we should be stripping symbols
    if(${_STRIP})
        _bcm_strip_symbols(${_MOD_NAME})
    endif()

    # Set the install target if the macro was passed one.
    _bcm_install_target(_OUT_STR ${_MOD_NAME} ${_EXPORT} _INSTALL_DIR ${_STRIP})

    # Add an interface libary with the name, ${_MOD_NAME}_${_HEADER_ONLY_EXT}, that can be used as a dependency
    # in place of hardcoded header paths. We want to include the definitions with this as well.
    _bcm_create_interface_lib(${_MOD_NAME}_${_HEADER_ONLY_EXT} ${_HEADER_ONLY_EXT})

    # Add to the global list
    list(APPEND BCM_ALL_SHARED_LIB_MODULES ${_MOD_NAME})
    set(BCM_ALL_SHARED_LIB_MODULES ${BCM_ALL_SHARED_LIB_MODULES} CACHE STRING "All Shared library Modules" FORCE)

    # Add header files and library dependencies, then clear the globals
    _bcm_module_add_target_specifics()
    if(NOT ${_NO_RESET})
        _bcm_module_globals_clear()
    endif()

    # If marked for RELEASE, install the binary if install macro exists
    if(_RELEASE)
        _bcm_release_binary(lib${_MOD_NAME}.so)
    endif()
    bcm_message(STATUS "Added 'shared_lib' rules for '${_MOD_NAME}'${_OUT_STR}")
endmacro(bcm_create_shared_lib_target)

#======
# Create the application target from the globals set. _MOD_NAME and _MOD_SRCS are required.
#
# @param ARGN           [in] Optional parameters as:
#                               - NO_RESET with any other options (Don't clear the global variables)
#                               - EXPORT (indicates whether to export the library or not)
#                               - STRIP (indicates that we should strip the symbols)
#                               - RELEASE (indicates that the resulting binary goes in host_driver_images
#                               - <install dir>  or EXPORT (indicates whether to export or put in install dir)
#======
macro(bcm_create_app_target)
    _bcm_param_exists(_NO_RESET NO_RESET ${ARGN})
    _bcm_param_exists(_EXPORT EXPORT ${ARGN})
    _bcm_param_exists(_STRIP STRIP ${ARGN})
    _bcm_param_exists(_RELEASE RELEASE ${ARGN})
    _bcm_find_install_dir(_INSTALL_DIR ${ARGN})

    # Store information that module is an application in the cache for other modules to see
    set(${_MOD_NAME}_TYPE app CACHE STRING "${_MOD_NAME} type" FORCE)

    _bcm_check_mandatory_variables(_MOD_NAME _MOD_SRCS)
    bcm_add_system_libraries_to_link(${_MOD_NAME}_SYSTEM_LIBRARIES EXECUTABLE)
    add_executable(${_MOD_NAME} ${_MOD_SRCS})
    # Prepare for batch compilation if necessary
    batch_compile_prepare()

    # Determine if we should be stripping symbols
    if(${_STRIP})
        _bcm_strip_symbols(${_MOD_NAME})
    endif()

    # Set the install target if the macro was passed one.
    _bcm_install_target(_OUT_STR ${_MOD_NAME} ${_EXPORT} _INSTALL_DIR ${_STRIP})

    # If this is the ARM toolchain, we want to set the target properties for static linking
    if(DEFINED ARM_TOOLCHAIN_PATH)
        set_target_properties(${_MOD_NAME} PROPERTIES
                              LINK_SEARCH_START_STATIC  1
                              LINK_SEARCH_END_STATIC    1)
    endif()

    # Add an interface libary with the name, ${_MOD_NAME}_${_HEADER_ONLY_EXT}, that can be used as a dependency
    # in place of hardcoded header paths. We want to include the definitions with this as well.
    _bcm_create_interface_lib(${_MOD_NAME}_${_HEADER_ONLY_EXT} ${_HEADER_ONLY_EXT})

    # Add to the global list
    list(APPEND BCM_ALL_APP_MODULES ${_MOD_NAME})
    set(BCM_ALL_APP_MODULES ${BCM_ALL_APP_MODULES} CACHE STRING "All Aplication Modules" FORCE)

    # Add header files and library dependencies, then clear the globals
    _bcm_module_add_target_specifics()
    if(NOT ${_NO_RESET})
        _bcm_module_globals_clear()
    endif()

    # If marked for RELEASE, install the binary if install macro exists
    if(_RELEASE)
        _bcm_release_binary(${_MOD_NAME})
    endif()
    bcm_message(STATUS "Added 'app' rules for '${_MOD_NAME}'${_OUT_STR}")
endmacro(bcm_create_app_target)

#======
# PRIVATE: Bring in the native build server compiler for the native_lib and native_app targets. We include
# the simulation definitions as they have the native compiler settings. The variables are in the context
# of the Aspen module using the native compiler, so it will not overwrite the cross-compiler for other
# Aspen modules.
#======
macro(_bcm_include_native)
    # For this target type, we want to bring in the native compiler if not already using it. Simulation would
    # already be using it, so need to bring it in for that case. Including 'sim' will set simulation build
    # to true, so make sure we restore it.
    if(NOT "${SIMULATION_BUILD}")
        unset(BCM_CFLAGS)
        unset(BCM_ASFLAGS)
        unset(BCM_LFLAGS)
        unset(ARM_TOOLCHAIN_PATH)
        set(_SAVED_SIMULATION_BUILD ${SIMULATION_BUILD})
        include(native)
        bcm_stringify_flags(CMAKE_C_FLAGS ${BCM_CFLAGS})
        bcm_stringify_flags(CMAKE_CXX_FLAGS ${BCM_CFLAGS})
        bcm_stringify_flags(CMAKE_ASM_FLAGS ${BCM_ASFLAGS})
        bcm_stringify_flags(CMAKE_EXE_LINKER_FLAGS ${BCM_LFLAGS})
        bcm_stringify_flags(SIMULATION_BUILD ${_SAVED_SIMULATION_BUILD})
    endif()
endmacro(_bcm_include_native)

#======
# Create the library target with the native compiler. This is the same as the bcm_create_lib_target(),
# except it builds with the simulation compiler. This is used to build tools (e.g. code generation) that must
# run on the build server.
#
# @param ARGN           [in] Optional parameters as:
#                               - NO_RESET with any other options (Don't clear the global variables)
#                               - EXPORT (indicates whether to export or put in install dir)
#======
macro(bcm_create_native_lib_target)
    _bcm_check_mandatory_variables(_MOD_NAME _MOD_SRCS)
    _bcm_include_native()
    bcm_create_lib_target(${ARGN})
endmacro(bcm_create_native_lib_target)

#======
# Create the application target with the native compiler. This is the same as the bcm_create_app_target(),
# except it builds with the simulation compiler. This is used to build tools (e.g. code generation) that must
# run on the build server. This macro will also add the resulting executable to the 'EXE' property on the target.
#
# @param ARGN           [in] Optional parameters as:
#                               - NO_RESET with any other options (Don't clear the global variables)
#                               - <install dir>  or EXPORT (indicates whether to export or put in install dir)
#======
macro(bcm_create_native_app_target)
    _bcm_check_mandatory_variables(_MOD_NAME _MOD_SRCS)
    _bcm_include_native()
    set(DISABLE_PLATFORM_APP_TARGET ON)
    bcm_create_app_target(${ARGN})
    unset(DISABLE_PLATFORM_APP_TARGET)

    # Make sure that cmake "forgets" that it might be cross-compiling
    if(NOT "${SIMULATION_BUILD}")
        set_target_properties(${_MOD_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${_MOD_NAME} SUFFIX "")
    endif()

    # Associate the resulting executable with the target
    set_target_properties(${_MOD_NAME} PROPERTIES EXE ${CMAKE_CURRENT_BINARY_DIR}/${_MOD_NAME})
endmacro(bcm_create_native_app_target)

#======
# PRIVATE: Add the rule for copying the source files used in Linux libraries and modules. The files are copied
# to the build tree and placed in a directory named with the _KERNEL_MOD_NAME_EXT value (k3rn3l). Using
# this subdirectory allows us to have the same source file, different objects and all objects in the build tree.
# A copy is used instead of a symlink because we want the command to only run on updates. This allows us to
# use the IMPLICIT_DEPENDS to get the header file dependencies as well. When this was done with symlink it caused
# a rebuild of the kernel modules everytime.
#
# @param TARGET         [out] Target that will link the source files
# @param SOURCE_LIST    [out] List of source files with absolute path
# @param ARGN           [in] 0 or more source files. If 0, nothing is done.
#======
macro(_bcm_kernel_copy_src TARGET SOURCE_LIST)
    unset(${SOURCE_LIST})

    foreach(_MOD_SRC ${ARGN})
        get_filename_component(_MOD_SRC_NAME ${_MOD_SRC} NAME)
        get_filename_component(_MOD_SRC_PATH ${_MOD_SRC} ABSOLUTE)

        # The linux library source files are copied to the k3rn3l subdirectory of this Aspen module's
        # binary tree.
        set(_MOD_DST_DIR    ${CMAKE_CURRENT_BINARY_DIR}/files)
        set(_MOD_DST_PATH   ${_MOD_DST_DIR}/${_MOD_SRC_NAME})

        # Create the rule to copy the source file. We use the IMPLICIT_DEPENDS on the source to get all the
        # header file dependencies.
        add_custom_command(OUTPUT ${_MOD_DST_PATH}
                           COMMAND mkdir -p ${_MOD_DST_DIR}
                           COMMAND cp -f ${_MOD_SRC_PATH} ${_MOD_DST_PATH}
                           IMPLICIT_DEPENDS C ${_MOD_SRC_PATH}
                           DEPENDS ${_MOD_SRC_PATH} ${_MOD_PUBLIC_DEPS} ${_MOD_PRIVATE_DEPS})

        # Add the source file to the source list so it can be used in the dependencies in the custom target
        list(APPEND ${SOURCE_LIST} ${_MOD_DST_PATH})
    endforeach(_MOD_SRC)

    # Create a target that will run all the copies. The target is returned to the caller so the
    # caller can use it in a dependency list.
    set(${TARGET} _copy_${_MOD_NAME}_srcs)
    add_custom_target(${${TARGET}} DEPENDS ${${SOURCE_LIST}})
endmacro(_bcm_kernel_copy_src)

#======
# Replace 'os' in the dependency lists with "os_linux". and define the non-header-only dependencies
# as 'kernel_target' type.
#
# @param DEPS           [in] Dependencies to redo
#======
macro(_bcm_set_kernel_dependencies DEPS)
    # Replace the OS dependency with the the os_linux
    if("os" IN_LIST ${DEPS})
        list(REMOVE_ITEM ${DEPS} os)
        list(APPEND ${DEPS} os_linux)
    endif()
    if("os_${_HEADER_ONLY_EXT}" IN_LIST ${DEPS})
        list(REMOVE_ITEM ${DEPS} os_${_HEADER_ONLY_EXT})
        list(APPEND ${DEPS} os_linux_${_HEADER_ONLY_EXT})
    endif()

    # Walk the dependencies and replace entries appropriately. If it has the '_kernel' or '_HDRONLY' extension,
    # we use it as-is. Any others we append '_HDRONLY' so no source or libraries are included (i.e. header-only
    # library).
    unset(_MY_DEPS)
    foreach(_MY_DEP ${${DEPS}})
        if(_MY_DEP MATCHES "_${_KERNEL_EXT}" OR _MY_DEP MATCHES "_${_HEADER_ONLY_EXT}")
            list(APPEND _MY_DEPS ${_MY_DEP})
        else()
            list(APPEND _MY_DEPS ${_MY_DEP}_${_HEADER_ONLY_EXT})
        endif()
    endforeach(_MY_DEP)
    set(${DEPS} ${_MY_DEPS})
endmacro(_bcm_set_kernel_dependencies)

#======
# Get the compile and link scripts for the kernel modules. We only need to do this once, not everytime through
# the macro below.
#======
bcm_find_cmake_script(_KMODULE_COMPILE_SCRIPT  kmodule_source_cache.sh)
bcm_find_cmake_script(_KMODULE_LINK_SCRIPT     kmodule_link.sh)
bcm_find_cmake_script(_KMODULE_AR_SCRIPT       kmodule_archive.sh)

#======
# PRIVATE: Common processing at the beginning of both the linux library and linux module. Here we validate
# that we can use the macro and create the rules for copying the source files. We also call the
# 'bcm_create_lib_target() to create an app and kernel version of the library.
#
# @param CACHE_FILE     [out] Base name of cache file used by scripts
# @param TYPE           [in] "LIB" or "MODULE"
# @param TARGET         [in] Name of the kernel target
#======
macro(_bcm_create_linux_common CACHE_FILE TYPE TARGET)
    # First validate that this is not the embedded subsystem and that the OS_KERNEL is linux, otherwise
    # the bcm_create_linux_<type>_target() macros can not be used.
    if("${SUBSYSTEM}" STREQUAL "embedded")
        bcm_message(FATAL_ERROR "Embedded subsystem can not create linux libraries/modules")
    elseif(NOT "${OS_KERNEL}" STREQUAL "linux")
        bcm_message(FATAL_ERROR "Can only build linux libraries/modules if kernel is linux")
    endif()

    # Next validate we got the inputs we are expecting.
    _bcm_check_mandatory_variables(_MOD_NAME _MOD_SRCS)

    # Rule to create the module source. The target here is a dependency of the _MOD_NAME target
    _bcm_kernel_copy_src(_KERNEL_COPY_TARGET _KERNEL_SRCS ${_MOD_SRCS})

    # For kernel builds we disable the extra warnings since we don't use them
    set(DISABLE_EXTRA_WARNINGS TRUE)

    # Add the kernel libraries we use. For Linux lib we use a static lib and for Linux module we use
    # a shared lib.
    unset(_LIB_TYPE)
    if(${TYPE} STREQUAL "MODULE")
        set(_LIB_TYPE SHARED)
    endif()
    add_library(${TARGET} ${_LIB_TYPE} ${_KERNEL_SRCS})
    add_dependencies(${TARGET} ${_KERNEL_COPY_TARGET})

    # Add the original module name as an interface lib for user space dependencies. Also create the header-only
    # target for those that reference it.
    add_library(${_MOD_NAME} INTERFACE)
    _bcm_create_interface_lib(${_MOD_NAME}_${_HEADER_ONLY_EXT} ${_HEADER_ONLY_EXT})

    # Add the definitions, header paths, dependencies to the targets
    set(_MY_MOD_SRCS ${_MOD_SRCS})
    unset(_MOD_SRCS)
    _bcm_module_add_target_specifics()

    set(_MOD_SRCS ${_MY_MOD_SRCS})
    _bcm_set_kernel_dependencies(_MOD_PUBLIC_DEPS)
    _bcm_set_kernel_dependencies(_MOD_PRIVATE_DEPS)
    _bcm_module_add_target_specifics(${TARGET})
    _bcm_module_globals_clear()

    # Make sure the files we use for collection of object files, header paths and definitions are cleared before we
    # start
    set(${CACHE_FILE} .compile)
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${${CACHE_FILE}}.objs)
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${${CACHE_FILE}}.incl)
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${${CACHE_FILE}}.defs)

    # Set the compile rule which is common for both linux lib and module
    set_property(TARGET ${TARGET} PROPERTY C_COMPILER_LAUNCHER ${_KMODULE_COMPILE_SCRIPT} ${${CACHE_FILE}})
endmacro(_bcm_create_linux_common)

#======
# Create the Linux library target from the globals set. _MOD_NAME is required.
# The linux library is only a collection of source files that have not been compiled yet. A linux module
# that has a dependency on the linux library will compile the source at that time. For this macro, we create
# a user level library and a kernel level library by using 'bcm_create_lib_target()'. We then add the
# CFLAGS and definitions to the kernel library + add the object files as a target property. Both the user
# space and kernel libraries are created as INTERFACE libraries since we don't want to build anything here.
# We don't check for the host subsystem here since this macro should never be called for embedded code.
#======
macro(bcm_create_linux_lib_target)
    set(_KERNEL_TARGET ${_MOD_NAME}_${_KERNEL_EXT})
    _bcm_create_linux_common(_KMODULE_SOURCE_CACHE_FILE LIB ${_KERNEL_TARGET})

    # Set the archive script to use
    set_property(TARGET ${_KERNEL_TARGET} PROPERTY RULE_LAUNCH_LINK ${_KMODULE_AR_SCRIPT})

    # Make sure we add any extra files to the clean rule for cleaning up kernel libraries
    set(_FILES_TO_CLEAN files .compile.incl .compile.objs .compile.defs)
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${_FILES_TO_CLEAN}")

    bcm_message(STATUS "Added 'linux_lib' rules for '${_MOD_NAME}'")
endmacro(bcm_create_linux_lib_target)

#======
# Create the Linux module target from the globals set. _MOD_NAME and _MOD_SRCS are required.
# The macro is only valid for the host subsystem and if the OS_KERNEL is linux. We use the validate macro
# to check this.
#
# @param ARGN           [in] Optional parameters as:
#                               - RELEASE (indicates that the resulting binary goes in host_driver_images
#                               - <install dir>  or EXPORT (indicates whether to export or put in install dir)
#======
macro(bcm_create_linux_module_target)
    _bcm_param_exists(_KERNEL_MOD_EXPORT EXPORT ${ARGN})
    _bcm_param_exists(_RELEASE RELEASE ${ARGN})
    _bcm_find_install_dir(_KERNEL_MOD_INSTALL_DIR ${ARGN})

    # Run the common linux target processing
    set(_KERNEL_TARGET ${_MOD_NAME}_${_KERNEL_EXT})
    _bcm_create_linux_common(_KMODULE_SOURCE_CACHE_FILE MODULE ${_KERNEL_TARGET})

    # Create the link command we will use. The link command needs to be a string, so we first create a list,
    # then convert to string. Note that we only include the CROSS_COMPILE if it is set.
    if(CROSS_COMPILE)
        set(_KMODULE_CROSS_COMPILE "-c ${CROSS_COMPILE}")
    endif(CROSS_COMPILE)
    if(GCC_VERSION)
        set(_KMODULE_GCC_VERSION "-h ${GCC_VERSION}")
    endif(GCC_VERSION)

    bcm_stringify_flags(_KMODULE_LINK_CMD
                        ${_KMODULE_LINK_SCRIPT} -l ${KERNELDIR} -a ${KERNEL_ARCH} ${_KMODULE_CROSS_COMPILE}
                        -m ${_MOD_NAME} -b ${CMAKE_CURRENT_BINARY_DIR} -f ${_KMODULE_SOURCE_CACHE_FILE}
                        -v ${CMAKE_VERBOSE_MAKEFILE} ${_KMODULE_GCC_VERSION})

    set_property(TARGET ${_KERNEL_TARGET} PROPERTY RULE_LAUNCH_LINK ${_KMODULE_LINK_CMD})

    # Make sure we add any extra files to the clean rule for cleaning up kernel modules
    set(_FILES_TO_CLEAN ${_MOD_NAME}.mod.c ${_MOD_NAME}.mod.o ${_MOD_NAME}.o built-in.o ${_MOD_NAME}.ko
        .${_MOD_NAME}.mod.o.cmd .${_MOD_NAME}.ko.cmd .${_MOD_NAME}.o.cmd .built-in.o.cmd files
        .compile.incl .compile.objs .compile.defs modules.order Module.symvers .tmp_versions)
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${_FILES_TO_CLEAN}")

    # Add the install for the kernel module
    _bcm_install_target(_OUT_STR ${CMAKE_CURRENT_BINARY_DIR}/${_MOD_NAME}.ko ${_KERNEL_MOD_EXPORT}
                        _KERNEL_MOD_INSTALL_DIR FALSE)

    # If marked for RELEASE, install the binary if install macro exists
    if(_RELEASE)
        _bcm_release_binary(${_MOD_NAME}.ko)
    endif()
    bcm_message(STATUS "Added 'linux module' rules for '${_MOD_NAME}'${_OUT_STR}")
endmacro(bcm_create_linux_module_target)

# Our build process requires that the cmake scan is initially run twice to generate a proper cache file. This allows
# us to put our build options anywhere in any CMake source file without having to pre-declare them. After the initial
# scan, CMake will automatically update the cache whenever a cmake source file changes.
#
# We force CMake to re-generate the Makefile the first time it is run by touching the cache file after it is initially
# generated. Unfortunately CMake doesn't normally let us execute commands after the cache is written, so we set up a
# listener on an internal variable that is accessed after the cache file is written, with a custom callback.
if(NOT EXISTS "${BUILD_TOP}/CMakeCache.txt")
    function(_BCM_POST_CACHE_WRITE_HOOK)
        # This will happen multiple times, but that's OK as long as the last one is after the cache is written.
        execute_process(COMMAND ${CMAKE_COMMAND} -E touch "${BUILD_TOP}/CMakeCache.txt")
    endfunction()
    variable_watch(CMAKE_SKIP_RPATH _BCM_POST_CACHE_WRITE_HOOK)
endif()
