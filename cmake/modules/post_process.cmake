# This CMake module covers post processing done after all the sub-directories have been added.
# The post processing takes advantage of the fact that all the targets have been defined. The
# first thing that is done is to take a set of target properties that we want to use as transitive
# and then making them as such. Once we have that, processing related to those parameters can be done.

#======
# Define the target properties that we want to be transitive. These will be 'flattened' so that if
# any one target looks a the properties, they will see all the entries bubbled up. It is guaranteed that
# the property will not have duplicate entries. Each property name will get prepended by INTERFACE_TRANSITIVE_
# to know where they are flattened to. Since the transitive properties have to start with INTERFACE,
# it is expected the entries will not include that.
#======
set(_TARGET_TRANSITIVE_PROPERTIES   LINK_LIBRARIES
                                    SYSTEM_LIBRARIES)

#======
# PRIVATE: Function to get the link libraries. For Interface libraries, this is the INTERFACE_LINK_LIBRARIES
# and for all others it is the LINK_LIBRARIES (to get both public and private). Returns a list of the
# library dependencies.
# @param LIBS_LIST      [out] List of libraries we want.
# @param MOD            [in] Module we want the dependencies from.
#======
function(_bcm_get_library_list_for_mod LIBS_LIST MOD)
    bcm_get_target_property(_MY_TYPE ${MOD} TYPE)

    if("${_MY_TYPE}" STREQUAL "INTERFACE_LIBRARY")
        # Interface libraries can only have INTERFACE_LINK_LIBRARIES
        bcm_get_target_property(_MOD_LIBS ${MOD} INTERFACE_LINK_LIBRARIES)
    else()
        # All other target types can have both public and private libraries
        bcm_get_target_property(_MOD_LIBS ${MOD} LINK_LIBRARIES)
    endif()

    # Make sure that all the Link Libraries are targets and, if not, we want to flag this as a fatal error. Anything
    # flagged indicates it is in the module's dependency list, but there is no build target for it.
    unset(_MISSING_DEPS)
    foreach(_LIB ${_MOD_LIBS})
        if(NOT TARGET ${_LIB})
            list(APPEND _MISSING_DEPS ${_LIB})
        endif()
    endforeach(_LIB)

    if(_MISSING_DEPS)
        bcm_message(STATUS "The following libraries for '${MOD}' were not found: ${_MISSING_DEPS}")
        list(REMOVE_ITEM _MOD_LIBS ${_MISSING_DEPS})
    endif()

    # If we got here we are good so update the output list
    set(${LIBS_LIST} ${_MOD_LIBS} PARENT_SCOPE)
endfunction(_bcm_get_library_list_for_mod)

#======
# PRIVATE: Function to bubble up the options we want to the given module target. The output is updated target
# properties for the given module.
#
# @param MOD            [in] module that we want the transitive properties added to
# @param ARGN           [in] list of targets that we want to bubble up
#======
function(_bcm_bubble_up_properties MOD)
    # Next get the transitive properties on the module and add the modules properties in
    foreach(_PROP ${_TARGET_TRANSITIVE_PROPERTIES})
        bcm_get_target_property(_MOD_INTERFACE_TRANSITIVE_${_PROP} ${MOD} INTERFACE_TRANSITIVE_${_PROP})
    endforeach(_PROP)

    # Now walk the dependencies and bubble up the values
    foreach(_DEP ${ARGN})
        foreach(_PROP ${_TARGET_TRANSITIVE_PROPERTIES})
            bcm_get_target_property(_DEP_INTERFACE_TRANSITIVE ${_DEP} INTERFACE_TRANSITIVE_${_PROP})

            if(DEFINED _DEP_INTERFACE_TRANSITIVE)
                list(APPEND _MOD_INTERFACE_TRANSITIVE_${_PROP} ${_DEP_INTERFACE_TRANSITIVE})
            endif()
        endforeach(_PROP)
    endforeach(_DEP)

    # Now make sure they are unique and update the module
    foreach(_PROP ${_TARGET_TRANSITIVE_PROPERTIES})
        if(DEFINED _MOD_INTERFACE_TRANSITIVE_${_PROP})
            list(REMOVE_DUPLICATES _MOD_INTERFACE_TRANSITIVE_${_PROP})
            set_target_properties(${MOD} PROPERTIES INTERFACE_TRANSITIVE_${_PROP}
                                  "${_MOD_INTERFACE_TRANSITIVE_${_PROP}}")
        endif()
    endforeach(_PROP)
endfunction(_bcm_bubble_up_properties)

#======
# PRIVATE: This function does the recursion through the depth of transitive link libraries to determine what target
# properties should be bubbled up to create the flattended property lists. We use the target property,
# INTERFACE_PROCESS_STATE with a value of 'undefined', 'continue', 'done'. The 'undefined' means we
# haven't done anything with that module yet, the 'started' keeps us from being stuck in circular dependencies
# and 'done' keeps us from reprocessing a library tree we've already seen.
#
# @param MOD            [in] Module name
# @param ARGN           [in] List of dependencies to look through for the module
#======
function(_bcm_recurse_transitive_dependencies MOD)
    if(TARGET ${MOD})
        bcm_get_target_property(_MOD_PROCESSED ${MOD} INTERFACE_PROCESS_STATE)

        if(NOT "${_MOD_PROCESSED}" STREQUAL "DONE")
            # This module has not been walked yet, so go ahead and do it.
            if(${ARGC} GREATER 1)
                foreach(_LIB ${ARGN})
                    # Check if each library is already processed and, if not, recurse to look at its dependencies.
                    if(TARGET ${_LIB})
                        bcm_get_target_property(_LIB_PROCESSED ${_LIB} INTERFACE_PROCESS_STATE)

                        if("${_LIB_PROCESSED}" STREQUAL "DONE")
                            # The library is already flattened (all transitive dependencies have been addressed).
                            # We can just add them in.
                            _bcm_bubble_up_properties(${MOD} ${_LIB})
                        elseif(NOT DEFINED _LIB_PROCESSED)
                            # The library is not yet processed, so dig in and see any below it.
                            set_target_properties(${MOD} PROPERTIES INTERFACE_PROCESS_STATE STARTED)
                            _bcm_get_library_list_for_mod(_MOD_LIBS ${_LIB})
                            _bcm_recurse_transitive_dependencies(${_LIB} ${_MOD_LIBS})
                            _bcm_bubble_up_properties(${MOD} ${_LIB})
                        endif()
                    endif()
                endforeach(_LIB)
            else()
                # We are at the bottom of this branch, so just add the properties to the transitive
                _bcm_bubble_up_properties(${MOD})
            endif()

            # Add in the module level settings to the transitive
            foreach(_PROP ${_TARGET_TRANSITIVE_PROPERTIES})
                bcm_get_target_property(_MOD_INTERFACE_TRANSITIVE ${MOD} INTERFACE_TRANSITIVE_${_PROP})
                if("${_PROP}" STREQUAL "LINK_LIBRARIES")
                    _bcm_get_library_list_for_mod(_MOD_THIS_PROP ${MOD})
                else()
                    bcm_get_target_property(_MOD_THIS_PROP ${MOD} INTERFACE_${_PROP})
                endif()

                if(DEFINED _MOD_THIS_PROP)
                    list(APPEND _MOD_INTERFACE_TRANSITIVE ${_MOD_THIS_PROP})
                    list(REMOVE_DUPLICATES _MOD_INTERFACE_TRANSITIVE)
                    set_target_properties(${MOD} PROPERTIES INTERFACE_TRANSITIVE_${_PROP}
                                          "${_MOD_INTERFACE_TRANSITIVE}")
                endif()
            endforeach(_PROP)

            # Mark this module as processed
            set_target_properties(${MOD} PROPERTIES INTERFACE_PROCESS_STATE DONE)
        endif()
    endif()
endfunction(_bcm_recurse_transitive_dependencies)

#======
# Walk the applications and shared libraries and get the transitive target properties as a flat list
# for each of the properties defined in _TARGET_TRANSITIVE_PROPERTIES. We can then use these for other
# processing (e.g. determine the "system" libraries that we link to for an application or shared library.
#======
macro(bcm_flatten_transitive_dependencies)
    foreach(_MOD  ${BCM_ALL_APP_MODULES} ${BCM_ALL_SHARED_LIB_MODULES})
        # For applications and shared libraries we need to look at both private and public dependencies
        # so we use the LINK_LIBRARIES property.
        get_target_property(_MOD_PUBLIC_LIBS ${_MOD} LINK_LIBRARIES)
        _bcm_recurse_transitive_dependencies(${_MOD} ${_MOD_PUBLIC_LIBS})

        # Cache the transitive dependencies for future reference
        foreach(_PROP ${_TARGET_TRANSITIVE_PROPERTIES})
            bcm_get_target_property(_MOD_TRANSITIVE_PROP ${_MOD} INTERFACE_TRANSITIVE_${_PROP})

            if(DEFINED _MOD_TRANSITIVE_PROP)
                set(${_MOD}_${_PROP} ${_MOD_TRANSITIVE_PROP} CACHE STRING
                    "Flat ${_PROP} for '${_MOD}'" FORCE)
            endif()
        endforeach(_PROP)

        # For the ARMCC case, we also want to collect the libraries and paths in the cache
        if(COMMAND armlink_post_process_lib_setup)
            armlink_post_process_lib_setup(${_MOD})
        endif()
    endforeach(_MOD)
endmacro(bcm_flatten_transitive_dependencies)

#======
# For optional dependencies, we need to walk all the modules added and look for definition of an optional
# dependency, then look if it exists. If an optional dependency is found and the dependency is a build target,
# add the depdendency to the module.
#======
macro(bcm_eval_optional_dependencies)
    foreach(_MOD  ${BCM_ALL_APP_MODULES} ${BCM_ALL_SHARED_LIB_MODULES} ${BCM_ALL_LIB_MODULES})
        foreach(_LEVEL PUBLIC PRIVATE INTERFACE)
            bcm_get_target_property(_MOD_OPTIONAL ${_MOD} INTERFACE_OPTIONAL_${_LEVEL}_LIBRARIES)

            foreach(_OPT ${_MOD_OPTIONAL})
                if(TARGET ${_OPT})
                    # The optional dependency exists as a target in our build so now it becomes
                    # mandatory. We can't use 'target_link_libraries' here because it can only
                    # be used in the subdirectory where the target was defined. Instead we directly
                    # add to the LINK_LIBRARIES.
                    bcm_get_target_property(_MOD_LINK_LIBS ${_MOD} INTERFACE_LINK_LIBRARIES)

                    if("${_LEVEL}" STREQUAL "PRIVATE")
                        # Indicates that we link to this, but do not make it transitive
                        list(APPEND _MOD_LINK_LIBS $<LINK_ONLY:${_OPT}>)
                    else()
                        # Public will link, Interface will not (according to CMake docs)
                        list(APPEND _MOD_LINK_LIBS ${_OPT})
                    endif()

                    set_target_properties(${_MOD} PROPERTIES INTERFACE_LINK_LIBRARIES "${_MOD_LINK_LIBS}")
                    bcm_message(STATUS "Optional dependency '${_OPT}' added to '${_MOD}'")
                endif()
            endforeach(_OPT)
        endforeach(_LEVEL)
    endforeach(_MOD)
endmacro(bcm_eval_optional_dependencies)
