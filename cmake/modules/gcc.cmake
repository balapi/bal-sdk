# CMake file that has the general GCC configurations. This can be used by both host builds
# and simulation builds.
include(option_macros)

#====
# Set Target related globals
#====
set(OS posix)
set(TOOLCHAIN gcc)

#====
# Make sure the PLATFORM variable represents a good value. It could have '-sim' in the name indicating simulation
# We want the actual platform within CMake.
#====
if("${PLATFORM}" MATCHES "-sim")
    string(REPLACE "-sim" "" _PLATFORM_NAME ${PLATFORM})
    set(PLATFORM ${_PLATFORM_NAME} CACHE STRING "Embedded platform type" FORCE)
endif()

#====
# Check the compiler with a library instead of executable. The executable CMake tries
# to build and run does not work on all versions of our build servers. Building to
# a library is sufficient to check the compiler and is how it is done in cross-compile.
#====
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#====
# Define the GCC_COMMON_CFLAGS that are common across host cross-compile and simulation
#====
set(GCC_COMMON_CFLAGS -std=c99 -MMD -MP -Werror -Wall -gdwarf-3 -fPIC)
set(GCC_COMMON_CXXFLAGS -MMD -MP -Werror -Wall -gdwarf-3 -fPIC)
add_definitions(-D_XOPEN_SOURCE=600)
if(OPEN_SOURCE)
    add_definitions(-DBCM_OPEN_SOURCE)
endif()
if(DBCM_OPEN_SOURCE_POLT_SIM)
    add_definitions(-DBCM_OPEN_SOURCE_SIM)
endif()


#====
# Define additional flags for more detailed error checking. These are included in build_macros.cmake
# unless the DISABLE_EXTRA_WARNINGS flag is set in the calling CMakeLists.txt file.
#====
set(BCM_EXTRA_WARNINGS -Wextra  -Wcast-align -Wcast-qual -Wchar-subscripts)
set(BCM_EXTRA_WARNINGS ${BCM_EXTRA_WARNINGS} -Wpointer-arith -Wredundant-decls)
set(BCM_EXTRA_WARNINGS ${BCM_EXTRA_WARNINGS} -Wparentheses -Wswitch -Wswitch-default -Wunused -Wuninitialized)
set(BCM_EXTRA_WARNINGS ${BCM_EXTRA_WARNINGS} -Wunused-but-set-variable -Wno-unused-parameter)
set(BCM_EXTRA_WARNINGS ${BCM_EXTRA_WARNINGS} -Wno-sign-compare -Wshadow -Wno-inline)
set(BCM_EXTRA_WARNINGS ${BCM_EXTRA_WARNINGS} -Wno-strict-aliasing -Wno-missing-field-initializers)

set(BCM_EXTRA_C_WARNINGS ${BCM_EXTRA_WARNINGS} -Wbad-function-cast -Wmissing-prototypes -Wnested-externs)
set(BCM_EXTRA_C_WARNINGS ${BCM_EXTRA_C_WARNINGS} -Wstrict-prototypes)

set(BCM_EXTRA_CXX_WARNINGS ${BCM_EXTRA_WARNINGS})

#====
# Set the linker command to use grouping for libraries. This will allow circular dependencies to get resolved.
# The system libraries are added to the end from the cache variable. We have already removed duplicates on the
# system libraries, but need to remove the ';' and add a '-l'. In order for this to work, the list of system
# libraries must be available now, which means they have to be in the cache. We rely on the double call to
# CMake from the Makefile wrapper when there is no cache yet and when CMake files change. This assures that
# the cache variable is set at time of building.
#====

# First set the default linker commands
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> -Wl,--start-group <LINK_LIBRARIES> -Wl,--end-group -Wl,--export-dynamic")

set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> -Wl,--start-group <LINK_LIBRARIES> -Wl,--end-group -Wl,--export-dynamic")

set(CMAKE_C_CREATE_SHARED_LIBRARY "<CMAKE_C_COMPILER> <CMAKE_SHARED_LIBRARY_C_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> -Wl,--start-group <LINK_LIBRARIES> -Wl,--end-group")

set(CMAKE_CXX_CREATE_SHARED_LIBRARY "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> -Wl,--start-group <LINK_LIBRARIES> -Wl,--end-group")

#====
# Now add a macro that will take the given library list and add it to the end of the link command. Note that
# a directory creating an executable or shared library that has system libs and then includes another directory
# that does the same can cause repeated system libs on the link command, if not careful. For this reason we
# temporarily turn the link command into a list so we can remove duplicates, then turn it back to a string.
#
# @param SYS_LIBS       [in] System libraries to add at the end of the link
# @param TARGET_TYPE    [in] Target type for determining the link commands
#====
macro(bcm_add_system_libraries_to_link SYS_LIBS TARGET_TYPE)
    if(DEFINED ${SYS_LIBS})
        # Here we consider whether there is a '-' at the head of the list entry indicating we already
        # have it in the right form. If no '-', then we prepend a '-l'. This allows special cases like
        # '-pthread' vs. 'pthread' to be used.
        unset(_MY_SYS_LIBS)

        foreach(_SYS_LIB ${${SYS_LIBS}})
            string(FIND ${_SYS_LIB} "-" _DASH_LOCATION)

            if(${_DASH_LOCATION} LESS 0)
                list(APPEND _MY_SYS_LIBS -l${_SYS_LIB})
            else()
                list(APPEND _MY_SYS_LIBS ${_SYS_LIB})
            endif()
        endforeach(_SYS_LIB)

        # Find the link commands we care about for this target type
        if("${TARGET_TYPE}" STREQUAL "SHARED_LIBRARY")
            set(_LINK_CMDS CMAKE_C_CREATE_SHARED_LIBRARY CMAKE_CXX_CREATE_SHARED_LIBRARY)
        elseif("${TARGET_TYPE}" STREQUAL "EXECUTABLE")
            set(_LINK_CMDS CMAKE_C_LINK_EXECUTABLE CMAKE_CXX_LINK_EXECUTABLE)
        endif()

        # Now go through the link commands, convert them to lists, add system libs, remove duplicates
        # and return to a string.
        foreach(_LINK_CMD ${_LINK_CMDS})
            string(REPLACE " " ";" _LINK_CMD_LIST "${${_LINK_CMD}}")
            list(APPEND _LINK_CMD_LIST ${_MY_SYS_LIBS})
            list(REMOVE_DUPLICATES _LINK_CMD_LIST)
            string(REPLACE ";" " " ${_LINK_CMD} "${_LINK_CMD_LIST}")
        endforeach(_LINK_CMD)
    endif()
endmacro(bcm_add_system_libraries_to_link)
