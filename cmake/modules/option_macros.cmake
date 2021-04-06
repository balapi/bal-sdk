# This file contains the macros needed for adding 'make' options. These are translated to CMake options
# on invocation of a build. They are also tracked so they can be parsed for the 'make help' target.
# These must be included before the first options are added.

#====
# Only add the included definitions if this file has not been previously included. We check this by looking
# for the custom target, 'help_params'.
#====
if(TARGET help_params)
    return()
endif()

#====
# Define the different option classifications we can have. We use this to loop through settings. If adding
# more option types, you will also need to add additional macros (i.e. bcm_make_<option type>_option) for
# those new types.
#====
set(_OPTION_TYPES   NORMAL DEBUG)

#====
# Macro to add a Make/CMake option with a default value and description. There must be one of these for
# each of the entries in _OPTION_TYPES, since we can't iterate to create macros.
#
# @param VAR            [in] Variable to set
# @param TYPE           [in] Variable type, can be "BOOL, FILEPATH, PATH, STRING"
# @param DESCRIPTION    [in] Description string for the variable
# @param VALUE          [in] Value(s) to set
#====
macro(bcm_make_normal_option VAR TYPE DESCRIPTION VALUE)
    _bcm_make_add_option(NORMAL ${VAR} ${TYPE} ${DESCRIPTION} ${VALUE})
endmacro(bcm_make_normal_option)

macro(bcm_make_debug_option VAR TYPE DESCRIPTION VALUE)
    _bcm_make_add_option(DEBUG ${VAR} ${TYPE} ${DESCRIPTION} ${VALUE})
endmacro(bcm_make_debug_option)

#====
# PRIVATE: Macro to set the cache vale and record the type and descripton. The type and description lists in the
# cache provide the information for the 'make help' parameter dump.
#
# @param OPTION_TYPE    [in] Type of option this is (DEBUG|NORMAL)
# @param VAR            [in] Variable to set
# @param TYPE           [in] Variable type, can be "BOOL, FILEPATH, PATH, STRING"
# @param DESCRIPTION    [in] Description string for the variable
# @param VALUE          [in] Value(s) to set
#====
macro(_bcm_make_add_option OPTION_TYPE VAR TYPE DESCRIPTION VALUE)
    # Set the option in the cache
    set(${VAR} ${VALUE} CACHE ${TYPE} ${DESCRIPTION})

    # Record the information in the cache for the 'make help'
    set(BCM_${OPTION_TYPE}_OPTIONS
       ${BCM_${OPTION_TYPE}_OPTIONS} ${VAR}
       CACHE STRING "${OPTION_TYPE} make options list" FORCE)
    set(BCM_${OPTION_TYPE}_DESCRIPTIONS
       ${BCM_${OPTION_TYPE}_DESCRIPTIONS} ${DESCRIPTION}
       CACHE STRING "${OPTION_TYPE} make option description list" FORCE)
endmacro(_bcm_make_add_option)

#====
# Iterate over the _OPTION_TYPES to clear the current cache values and create the help targets.
# The help targets provide the parameter dump and are run either at the top of the build tree or
# from the Makefile wrapper.
#====
unset(HELP_PARAMS_TARGET_LIST)

foreach(_OPTION_TYPE ${_OPTION_TYPES})
    string(TOLOWER ${_OPTION_TYPE} _OPTION_TYPE_LC)

    unset(BCM_${_OPTION_TYPE}_OPTIONS CACHE)
    unset(BCM_${_OPTION_TYPE}_DESCRIPTIONS CACHE)


    # Create help targets for the 'make' options available
    add_custom_target(help_${_OPTION_TYPE_LC}_params
                      COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/cmake/scripts/find_options.py
                              ${_OPTION_TYPE_LC} ${CMAKE_CURRENT_BINARY_DIR})
    list(APPEND HELP_PARAMS_TARGET_LIST help_${_OPTION_TYPE_LC}_params)
endforeach(_OPTION_TYPE)

#====
# Help target that will execute all the option type helps.
#====
add_custom_target(help_params
                  DEPENDS ${HELP_PARAMS_TARGET_LIST})
