# Utilities macros and functions available to the CMake users
# The following are available:
# - bcm_create_global_compile_definition    - Creates a global compile option created from CMake settings
# - bcm_message                             - Wrapper on CMake 'message' that provides debug output
# - bcm_find_absolute_path                  - Find the absolute path for the given absolute or relative path
# - bcm_find_relative_path                  - Find the relative path for the given absolute or relative path
# - bcm_prepend_source_path                 - Prepend a path to a list of directories
# - bcm_get_target_property                 - Run the CMake 'get_target_property', but return 'unset' if not found
# - bcm_find_cmake_script                   - Finds a path to the requested script in any of the CMake module dirs
# - bcm_string_remove_duplicates            - Convert the given string to a list and remove dups, then back to string
# - bcm_append_additional_clean_files       - Append additional clean files in the directory, used for artifact clean

#====
# Macro to create a compile definition by taking the variable given, making it uppercase and appending to the
# given value. For example: BCM_OS_POSIX would be created by passing BCM_OS as the preamble and "posix" as the
# append string.
#
# @param PREAM          [in] Preamble to the definition
# @param APPEND_STR     [in] String to capatiliza and append to the PREAM
#====
macro(bcm_create_global_compile_definition PREAM APPEND_STR)
    string(TOUPPER ${APPEND_STR} _CAP_APPEND_STR)
    add_definitions(-D${PREAM}_${_CAP_APPEND_STR})
endmacro(bcm_create_global_compile_definition)

#====
# Macro for Broadcom messages. These messages will have a common preamble for easy parsing of CMake output
# to find things specific to what we've done. The parameters are the same as CMake's 'message' function.
# These messages will only come out when the V=y is used (CMAKE_VERBOSE_MAKEFILE).
#
# @param TYPE           [in] Message type (e.g. INFO, STATUS) as defined by CMake 'message()'
# @param STR            [in] Message string
#====
macro(bcm_message TYPE STR)
    if(${CMAKE_VERBOSE_MAKEFILE} OR ("${TYPE}" STREQUAL "FATAL_ERROR"))
        # If the type is not "INFO", the message call does not put a space between type and mesage.
        # we take care of that here.
        if(NOT "${TYPE}" STREQUAL "STATUS")
            set(SPACE " ")
        endif()
        message(${TYPE} "${SPACE}BCM ${PLATFORM} ${SUBSYSTEM}: ${STR}")
    endif()
endmacro(bcm_message)

#====
# Get the absolute path to the given directory or file. The given directory can either already be absolute
# or relative.
#
# @param ABSOLUTE_PATH  [out] Resulting path
# @param DIR_OR_FILE    [in] Directory or file we want to have an absolute path to
#====
macro(bcm_find_absolute_path ABSOLUTE_PATH DIR_OR_FILE)
    if(IS_ABSOLUTE "${DIR_OR_FILE}")
        set(${ABSOLUTE_PATH} ${DIR_OR_FILE})
    else()
        set(${ABSOLUTE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/${DIR_OR_FILE})
    endif()
endmacro(bcm_find_absolute_path)

#====
# Get the relative path to the given directory or file. The given directory can either already be absolute
# or relative. This will return relative to CMAKE_CURRENT_SOURCE_DIR.
#
# @param RELATIVE_PATH  [out] Resulting path
# @param DIR_OR_FILE    [in] Directory or file we want to have an absolute path to
#====
macro(bcm_find_relative_path RELATIVE_PATH DIR_OR_FILE)
    if(IS_ABSOLUTE "${DIR_OR_FILE}")
        file(RELATIVE_PATH ${RELATIVE_PATH} ${CMAKE_CURRENT_SOURCE_DIR} ${DIR_OR_FILE})
    else()
        set(${RELATIVE_PATH} ${DIR_OR_FILE})
    endif()
endmacro(bcm_find_relative_path)

#====
# Macro to prepend a directory to a list of files. Useful for things like prepending the ASIC revision to a
# list of driver source files.
#
# @param RESULT_LIST    [out] List of source paths relative to the SRC_PATH.
# @param SRC_PATH       [in] Preamble source path to apply to each list entry.
# @param ARGN           [in] Variable List of source files
#====
macro(bcm_prepend_source_path RESULT_LIST SRC_PATH)
    string(REGEX REPLACE "([^;]+)" "${SRC_PATH}/\\1" ${RESULT_LIST} "${ARGN}")
endmacro(bcm_prepend_source_path)

#======
# Macro to get a property and make it unset if not found
#
# @param OUTPUT         [out] variable to fill in
# @param MOD            [in] module to get property for
# @param PROPERTY       [in] property to retrieve
#======
macro(bcm_get_target_property OUTPUT MOD PROPERTY)
    get_target_property(_OUTPUT ${MOD} ${PROPERTY})

    if("${_OUTPUT}" MATCHES ".*-NOTFOUND")
        unset(${OUTPUT})
    else()
        set(${OUTPUT} ${_OUTPUT})
    endif()
endmacro(bcm_get_target_property)

#======
# Find the path to a CMake support script. We look at all the CMAKE_MODULE_PATH entries to find it.
#
# @param SCRIPT_PATH    [out] Apsolute path to the CMake support script
# @param SCRIPT_NAME    [in] Script to find
#======
macro(bcm_find_cmake_script SCRIPT_PATH SCRIPT_NAME)
    string(REGEX REPLACE "([^;]+)" "\\1/../scripts/${SCRIPT_NAME}" CMAKE_MODULE_SCRIPT_PATH "${CMAKE_MODULE_PATH}")
    file(GLOB ${SCRIPT_PATH} LIST_DIRECTORIES FALSE ${CMAKE_MODULE_SCRIPT_PATH})
endmacro(bcm_find_cmake_script)

#======
# Convert the given string to a list and remove duplicates. After done, convert back to a string and return.
# This is used for things like compile flags where we want to append flags that are string based. By using
# this function we can avoid duplicates.
#
# @param OUTPUT_STRING  [out] String to return
# @param INPUT_STRING   [in] String to remove duplicates from
#======
function(bcm_string_remove_duplicates OUTPUT_STRING INPUT_STRING)
    # Convert the input string to a list and remove duplicates
    string(REPLACE " " ";" _INPUT_STRING_LIST "${INPUT_STRING}")
    list(REMOVE_DUPLICATES _INPUT_STRING_LIST)

    # Convert the list back to a string
    string(REPLACE ";" " " _OUTPUT_STRING "${_INPUT_STRING_LIST}")
    set(${OUTPUT_STRING} ${_OUTPUT_STRING} PARENT_SCOPE)
endfunction(bcm_string_remove_duplicates)

#======
# Add the software version for embedded or host to the CMake cache. This will also create the release info log
# used in the release package creation.
#
# @param SRC_FILE       [in] Header file containing the version information.
# @param LOG_FILE       [in] Where to write the log information in the artifacts.
#======
function(bcm_cache_sw_version SRC_FILE LOG_FILE)
    set(_VALUES_TO_GET _MAJOR_VER _MINOR_VER _REVISION_VER)

    foreach(_MY_VALUE ${_VALUES_TO_GET})
        execute_process(COMMAND grep ${_MY_VALUE} ${SRC_FILE}
                        COMMAND awk "{print $3}"
                        OUTPUT_VARIABLE ${_MY_VALUE})
        string(STRIP ${${_MY_VALUE}} ${_MY_VALUE})
    endforeach(_MY_VALUE)

    set(SW_VERSION_MAJOR ${_MAJOR_VER} CACHE STRING "SW Version Major" FORCE)
    set(SW_VERSION_MINOR ${_MINOR_VER} CACHE STRING "SW Version Minor" FORCE)
    set(SW_VERSION_REVISION ${_REVISION_VER} CACHE STRING "SW Version Revision" FORCE)

    file(WRITE ${LOG_FILE}
        "SW_VERSION_MAJOR=${SW_VERSION_MAJOR}\n"
        "SW_VERSION_MINOR=${SW_VERSION_MINOR}\n"
        "SW_VERSION_REVISION=${SW_VERSION_REVISION}\n")

endfunction(bcm_cache_sw_version)

#======
# Append to the current directories list of additional files to clean when 'make clean' is done. This is used
# for files that CMake is not aware of.
#
# @param ARGN           [in] Additional files/directories to clean in the current binary directory.
#======
function(bcm_append_additional_clean_files)
    get_directory_property(_MY_PROPS ADDITIONAL_MAKE_CLEAN_FILES)
    list(APPEND _MY_PROPS ${ARGN})
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${_MY_PROPS}")
endfunction(bcm_append_additional_clean_files)

#======
# Convert the given flag list to a string. Used for setting CMAKE_<LANG>_FLAGS
#
# @param OUT_VAR        [out] Variable to set with the string
# @param ARGN           [in] List to stringify
#======
macro(bcm_stringify_flags OUT_VAR)
    string(REPLACE ";" " " ${OUT_VAR} "${ARGN}")
endmacro(bcm_stringify_flags)

#======
# This function will create a target from the given output files and then apply that as a dependency to the
# master target. The individual targets are named with an increasing index. To avoid issues with parallel builds
# we make each new target dependent on the previous one. That way one codegen has to complete before the next.
#
# @param MASTER_TARGET  [in] Master target relying on the given files
# @param ARGN           [in] Files that we want to add as a dependency
#======
function(bcm_add_output_file_dependency MASTER_TARGET)
    set(_MY_FILES ${ARGN})

    # If this is the first time in the master target is not present. Use this to reset the index count
    if(TARGET ${MASTER_TARGET})
        set(_MY_INDEX ${_BCM_${MASTER_TARGET}_INDEX})
        set(_LAST_TARGET ${MASTER_TARGET}_${_MY_INDEX})
        math(EXPR _MY_INDEX ${_MY_INDEX}+1)
    else()
        set(_MY_INDEX 1)
        set(_LAST_TARGET ${MASTER_TARGET})
        add_custom_target(${MASTER_TARGET})
    endif()

    set(_THIS_TARGET ${MASTER_TARGET}_${_MY_INDEX})

    # Add the target that contains these files. We do this because files can not be added to a target with
    # 'add_dependencies'. Only targets can be added that way.
    add_custom_target(${_THIS_TARGET} DEPENDS ${_MY_FILES})
    add_dependencies(${_LAST_TARGET} ${_THIS_TARGET})

    # Update the index and write to the cache.
    set(_BCM_${MASTER_TARGET}_INDEX ${_MY_INDEX} CACHE INTERNAL "Count for ${MASTER_TARGET} dependencies" FORCE)
endfunction(bcm_add_output_file_dependency)

#======
# Macro to remove language flags for a module. This allows overrides of flags for a particular module.
#
# @param LANG           [in] Language for the flags (e.g. C, CXX)
# @param ARGN           [in] List of flags to remove (Can be regular expressions)
#======
macro(bcm_module_remove_flags LANG)
    foreach(_FLAG ${ARGN})
        string(REGEX REPLACE ${_FLAG} "" CMAKE_${LANG}_FLAGS ${CMAKE_${LANG}_FLAGS})
    endforeach(_FLAG)
endmacro(bcm_module_remove_flags)

#======
# Thee following functions suppprt a "key-value" idea where we  use a list to collect 'name' - 'value' pairs,
# where the value can be a list. We only do an add or find, there is no need to do a remove for the CMake
# use cases.
#
# The value can be a list, but in order to safely store a list in a list, we need to change the ';' to
# another character (we use '?').
#======

# Add to key-value list. If the key is already present, append the values given to the current values
#
# @param KEY_VALUE_LIST [i/o] Current key-value variable, both input and return value
# @param KEY            [in] Key to use
# @param ARGN           [in] List of values to add
#
function(bcm_key_value_add KEY_VALUE_LIST KEY)
    set(_NEW_VALUES ${ARGN})

    # Make sure we were given values to use
    if(NOT _NEW_VALUES)
        message(FATAL_ERROR "ERROR: No new values given to the CMake key-value")
    endif()

    # Check if the element exists in the list and get the index if it does
    list(FIND ${KEY_VALUE_LIST} ${KEY} _KEY_LOCATION)

    if(_KEY_LOCATION LESS 0)
        # No entry yet, so convert the value to a string and add it.
        string(REPLACE ";" "?" _CONVERTED_NEW_VALUES "${_NEW_VALUES}")
        list(APPEND ${KEY_VALUE_LIST} ${KEY} "${_CONVERTED_NEW_VALUES}")
    else()
        # Already exists, get the next index (value) and then remove that element
        math(EXPR _VALUE_LOCATION ${_KEY_LOCATION}+1)
        list(GET ${KEY_VALUE_LIST} ${_VALUE_LOCATION} _VALUE)
        list(REMOVE_AT ${KEY_VALUE_LIST} ${_VALUE_LOCATION})

        # Now convert the value to a list, append the new values and convert back to string
        string(REPLACE "?" ";" _LIST_VALUE "${_VALUE}")
        list(APPEND _LIST_VALUE ${_NEW_VALUES})
        string(REPLACE ";" "?" _VALUE "${_LIST_VALUE}")

        # Re-add the values back to the key value list. If value was last element, use 'append'
        list(LENGTH ${KEY_VALUE_LIST} _LIST_LENGTH)
        if(${_VALUE_LOCATION} EQUAL ${_LIST_LENGTH})
            list(APPEND ${KEY_VALUE_LIST} "${_VALUE}")
        else()
            list(INSERT ${KEY_VALUE_LIST} ${_VALUE_LOCATION} "${_VALUE}")
        endif()
    endif()

    # Make sure the caller gets the updates
    set(${KEY_VALUE_LIST} ${${KEY_VALUE_LIST}} PARENT_SCOPE)
endfunction(bcm_key_value_add)

# Get the values at the given key from the key-value list
#
# @param VALUE          [out] Variable to return the value in
# @param KEY_VALUE_LIST [in] List containing the key value pairs
# @param KEY            [in] Key used to find the values
function(bcm_key_value_get VALUE KEY_VALUE_LIST KEY)
    # Check if the element exists in the list and get the index if it does
    list(FIND ${KEY_VALUE_LIST} ${KEY} _KEY_LOCATION)

    if(_KEY_LOCATION LESS 0)
        message(FATAL_ERROR "ERROR: no entry found in the key-value list for key=${KEY}")
    endif()

    math(EXPR _VALUE_LOCATION ${_KEY_LOCATION}+1)
    list(GET ${KEY_VALUE_LIST} ${_VALUE_LOCATION} _VALUE)
    string(REPLACE "?" ";" _LIST_VALUE "${_VALUE}")

    # Make sure the caller gets the updates
    set(${VALUE} ${_LIST_VALUE} PARENT_SCOPE)
endfunction(bcm_key_value_get)

#======
# Convert a version to a single number that can be used in the C pre-processor for comparisons. Primary use
# case is the SDK version.
#
# @param SINGLE_NUMBER      [out] Resulting calculated single number representing the version
#                                 (XX.YY.ZZ -> XXYYZZ, with padding to 2 digits on 2nd and 3rd numbers)
#======
function(bcm_convert_version_to_single_number SINGLE_NUMBER VERSION_NUMBER)
    # Split the version number into a list and pop the first entry
    string(REPLACE "." ";" _VERSION_NUMBER_LIST "${VERSION_NUMBER}")
    list(GET _VERSION_NUMBER_LIST 0 _THIS_NUM)
    list(REMOVE_AT _VERSION_NUMBER_LIST 0)
    set(_SINGLE_NUMBER "${_THIS_NUM}")

    # Now get the follow-on digits and pad to a byte
    foreach(_THIS_NUM ${_VERSION_NUMBER_LIST})
        string(LENGTH "${_THIS_NUM}" _THIS_NUM_LENGTH)
        if(${_THIS_NUM_LENGTH} EQUAL 1)
            set(_THIS_NUM_PADDED "0${_THIS_NUM}")
        else()
            set(_THIS_NUM_PADDED "${_THIS_NUM}")
        endif()
        string(APPEND _SINGLE_NUMBER ${_THIS_NUM_PADDED})
    endforeach(_THIS_NUM)

    set(${SINGLE_NUMBER} ${_SINGLE_NUMBER} PARENT_SCOPE)
endfunction(bcm_convert_version_to_single_number)
