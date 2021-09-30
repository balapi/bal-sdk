# Top level makefile for generating the build tree. The makefile is a wrapper to the CMake call
# to simplify the interface. See the 'make help' for more information on what can be done here.
#
# The build artifacts will be under the 'build' directory.
#
# Artifacts (e.g. executables, images, kernel modules, etc. Will be added to the build tree
# in the designated install path. For consistency with Maple, by default the install path will
# be the directory 'fs' (e.g. /build/embedded-aspen/fs.
#

#====
# Top level definitions used before CMake
#====
TOP_DIR             := $(shell pwd)
BUILD_TOP_DIR       ?= ./build
BOARD               ?= sim
V                   ?= n

ifneq (,$(wildcard ./netconf_server))
    NETCONF_PRESENT := y
    NETCONF_SERVER  ?= y
    NETCONF_SERVER_OPT     := -DNETCONF_SERVER:BOOL=$(NETCONF_SERVER)
endif
ifneq (,$(wildcard ./onu_mgmt/tr451_vomci_polt)$(wildcard ./tr451_vomci_polt))
    TR451_VOMCI_POLT ?= y
    TR451_VOMCI_POLT_OPT   := -DTR451_VOMCI_POLT:BOOL=$(TR451_VOMCI_POLT)
endif
OPEN_SOURCE         := y

ifeq ("$V", "n")
    SILENT              := @
    CMAKE_VERBOSE       := OFF
    BCM_MAKE_OPTIONS    := --no-print-directory
else
    CMAKE_VERBOSE       := ON
endif

#====
# Build artifact directory paths
#====
HOST_ARTIFACTS          := $(BUILD_TOP_DIR)
HOST_CACHE_MD5SUM       := $(shell md5sum $(HOST_ARTIFACTS)/CMakeCache.txt 2>/dev/null)

#====
# Variables used in the 'clean' rules. The lower case part is to support meta rule resolution
#====
ALL_clean_ARTIFACTS             := $(wildcard $(BUILD_TOP_DIR)/Makefile)
ALL_clean_cache_ARTIFACTS       := $(wildcard $(BUILD_TOP_DIR)/CMakeCache.txt)

#====
# Determine the flags we pass to CMake that are common for host or embedded. The definitions set
# here can be viewed in the <artifact tree>/CMakeCache.txt file. All variables that are overridden
# on the command line (e.g. "UT=y") are passed through to CMake transparently. Additionally, CMake
# has a bool for enabling or disabling verbose info from the Makefiles. If the V variable is set,
# the verbose will be enabled. If not set the verbose will be disabled.
#====
BCM_CMAKE_USER_VARS = $(patsubst %,-D%,$(filter-out BUILD_TOP_DIR=%,$(filter-out V=%,$(MAKEOVERRIDES))))
MAKE_PID = $(shell echo $$PPID)
JOB_FLAG := $(filter -j%, $(subst -j, -j, $(shell ps T | grep "^\s*$(MAKE_PID).*$(MAKE)")))

BCM_CMAKE_OPTIONS = $(BCM_CMAKE_USER_VARS) \
                    $(NETCONF_SERVER_OPT) \
                    $(TR451_VOMCI_POLT_OPT) \
                    -DOPEN_SOURCE=$(OPEN_SOURCE) \
                    -DBOARD:STRING=$(BOARD) \
                    -DCMAKE_VERBOSE_MAKEFILE:BOOL=$(CMAKE_VERBOSE) 

#====
# Definitions of commands used in the build rules. Currently: cmake generation, docker use check and
# clean.
#====
BCM_CMAKE_CMD      = cd $(BUILD_DIR) && \
                     cmake -DCMAKE_TOOLCHAIN_FILE=cmake/modules/$(TOOLCHAIN).cmake \
                           $(BCM_CMAKE_OPTIONS) \
                           -DSUBSYSTEM:STRING=$(SUBSYSTEM) $(TOP_DIR)

BCM_CLEAN_CMD      = test "$(ALL_$@_ARTIFACTS)" != ""  && \
                     for this_dir in $(ALL_$@_ARTIFACTS); do \
                        if test $(BCM_CLEAN_CACHE) -eq 1; then \
                        	echo -n "Cleaning file $$this_dir...."; \
                            rm -f $$this_dir; \
                        else \
                        	echo -n "Cleaning directory $$(dirname $$this_dir)...."; \
                            (cd $$(dirname $$this_dir) && rm -f CMakeCache.txt && $(MAKE) $(BCM_MAKE_OPTIONS) clean);\
                        fi; \
                        echo "done"; \
                     done || echo "Nothing to be done for '$@'"

ifneq ("$NETCONF_PRESENT", "y")
    INSTALL_INCLUDE_TARGET = github_install_include
endif

#====
# Default build rule
#====
all: host

PHONY += all

#====
# Rules for generating the CMake build trees. For each subsystem it is possible the CMake command line
# may be called twice. This is to support a modularization use case where we want to place cache options
# (bcm_make_<type>_option() macros) with the module that is associated (e.g. CLI=y|n in the
# cli/CMakeLists.txt file).
#
# To support the modularity we want, we would need to run the CMake command line twice before doing the build.
# Since this has a slight impact on the build time, we will only do this if any CMakeLists.txt files have
# changed in the tree and the CMakeCache.txt file is now out of date. If no CMakeLists.txt file changes,
# we only run the CMake command line once per invocation.
#====

cmake-host: BUILD_DIR := $(HOST_ARTIFACTS)
cmake-host: TOOLCHAIN := $(BOARD)
cmake-host:
	$(SILENT)mkdir -p $(BUILD_DIR)
	$(SILENT)$(BCM_DOCKER_CHECK)
	$(SILENT)$(BCM_CMAKE_CMD)
	$(SILENT)if test "$$(md5sum $(HOST_ARTIFACTS)/CMakeCache.txt)" != "$(HOST_CACHE_MD5SUM)"; then \
        $(BCM_CMAKE_CMD); \
     fi
PHONY += cmake-host

#====
# Rules for just generating the build artifact tree. The CMake generation is done only, no make is done
# afterwards. This can be used if you don't want to build an entire 'embedded' or 'host'. For example, you
# might just want to build unit tests in one subsystem.
#====
buildtree: cmake-host
PHONY += buildtree

#====
# Rules for the subsystem builds. These will update the artifact tree with CMake and then run a make
# in that tree. The 'make install' is used so the results will be in the 'fs' directory at the top
# of the artifact tree.
#====
host: cmake-host
	$(SILENT)cd $(HOST_ARTIFACTS) && $(MAKE) $(BCM_MAKE_OPTIONS) install $(INSTALL_INCLUDE_TARGET)
PHONY += host

#====
# Clean rules for build and artifact trees. The 'clean', 'clean_host', 'clean_embedded' are a 'make clean'
# in the artifact tree. The 'make clean' target that is run was generated by CMake and will just clean
# the build artifacts. The CMake generated tree will remain. To clean the CMake tree, use the 'make clean_all'
# which just removes the whole 'build' directory.
#====
clean: BCM_CLEAN_CACHE = 0
clean:
	$(SILENT)$(BCM_CLEAN_CMD)
PHONY += clean

clean_cache: BCM_CLEAN_CACHE = 1
clean_cache:
	$(SILENT)$(BCM_CLEAN_CMD)
PHONY += clean_cache

clean_all:
	@echo -n "Removing the build directory...."
	$(SILENT)rm -rf $(BUILD_TOP_DIR)
	@echo "done"
PHONY += clean_all

#====
# Make help targets
#====
.NOTPARALLEL:
help_targets:
	@echo
	@echo "Make Targets:"
	@echo "   help                      - Help for all targets, including target types"
	@echo "   all                       - Build the source for the host board (default target)"
	@echo "   buildtree                 - Just run the CMake configuration, no build"
	@echo "   clean                     - Do a 'make clean' in the host and embedded build trees, includes CMake cache"
	@echo "   clean_cache               - Remove the CMake cache for the host and embedded build trees"
	@echo "   clean_all                 - Remove all the build artifacts"
PHONY += help_targets

help_params:
	@echo
	@echo "Make Parameters Available for Host"
	@echo "   BOARD                     - Host board type [current='$(BOARD)']"
	@echo "   KERNELDIR                 - Top of the kernel source directory [current='$(KERNELDIR)']"
	@echo "   KERNEL_OUTDIR             - Top of the kernel build directory (default KERNELDIR) [current='$(KERNEL_OUTDIR)']"
	@echo "   BUILD_TOP_DIR             - Where to place the build artifacts [current='$(BUILD_TOP_DIR)']"
	@test -s $(HOST_ARTIFACTS)/CMakeCache.txt && (cd $(HOST_ARTIFACTS) && $(MAKE) -s help_normal_params) || \
								  echo "(Run 'make buildtree' to see the full set of options)"
	@echo
	@echo "Make Debug Parameters Available for Host"
	@echo "   V                         - Turn on or off make verbosity, =y to turn on [current='$(if $(V),y,n)']"
PHONY += help_params

help: help_targets help_params
PHONY += help
