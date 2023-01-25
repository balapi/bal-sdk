# CMake module for defining compile of either Host or Embedded for simulation envirionment.
# Simulation is anything built to run on a Linux host and uses the native gcc compiler.

#====
# Bring in the common GCC settings
#====
include(gcc)

#====
# Compile definitions specific to building a simulation target
#====
set(SIMULATION_BUILD y)
add_definitions(-DSIMULATION_BUILD)

#====
# Add the compile and link flags we use for simulation
#====
set(BCM_CFLAGS      ${GCC_COMMON_CFLAGS} -ggdb -O2)
set(BCM_CXXFLAGS    ${GCC_COMMON_CXXFLAGS} -ggdb -O2)

set(BCM_LFLAGS              ${BCM_CFLAGS})
set(BCM_EXTRA_C_WARNINGS    ${BCM_EXTRA_C_WARNINGS} -Wno-switch-bool)
set(BCM_OBJCOPY             objcopy)

#====
# Add in the common lint flags
#====
set(BCM_CFLAGS   ${BCM_CFLAGS} ${GCC_COMMON_CFLAGS})
set(BCM_CXXFLAGS ${BCM_CXXFLAGS} ${GCC_COMMON_CXXFLAGS})

set(BCM_EXTRA_C_WARNINGS    ${BCM_EXTRA_C_WARNINGS} -Wno-switch-bool)

#====
# Unset toolchain variables that might've been set by platform/board-specific target
# Set the compiler to use gcc. If not set, it would default to 'cc' which is 'gcc' anyway, so this isn't
# strictly necessary.
#====
set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER_AR ar)
set(CMAKE_CXX_COMPILER_AR ar)
set(CMAKE_C_COMPILER_RANLIB ranlib)
set(CMAKE_CXX_COMPILER_RANLIB ranlib)
set(CMAKE_LINKER gcc)

#====
# Set the supported manifest files (a.k.a. configuration profiles)
#====
set(BCM_MANIFESTS x86)

#====
# --host setting for 3rd-party packages using automake
#====
set(BCM_CONFIG_HOST x86_64-linux)
