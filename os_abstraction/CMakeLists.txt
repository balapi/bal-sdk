bcm_module_name(os)

bcm_module_header_paths(PUBLIC ${OS} .)
bcm_module_dependencies(PUBLIC ${SUBSYSTEM}_config)

bcm_make_debug_option(OS_HEAP_DEBUG      BOOL    "Enable heap debugging" n)
bcm_make_debug_option(OS_BLK_POOL_DEBUG  BOOL    "Enable block pool debugging" n)
bcm_make_debug_option(OS_TIMER_DEBUG     BOOL    "Enable timer debugging" n)
bcm_make_debug_option(OS_MEM_CHECK       BOOL    "Enable dynamic memory block boundary check" n)

if("${OS}" STREQUAL "threadx")
    bcm_module_dependencies(PUBLIC threadx bsp)
    bcm_module_definitions(PUBLIC -DBCMOS_TRACE_IN_DEV_LOG)
    bcm_module_definitions(PUBLIC -DBCMOS_HEALTH_CHECK_ENABLED)
elseif("${OS}" STREQUAL "posix")
    bcm_module_definitions(PUBLIC -DBCMOS_MSG_QUEUE_DOMAIN_SOCKET
                                  -DBCMOS_MSG_QUEUE_UDP_SOCKET)

    bcm_module_system_libraries(pthread rt m)
elseif("${OS}" STREQUAL "cfe")
    bcm_module_dependencies(PRIVATE sys)
    bcm_module_header_paths(PUBLIC ${SOURCE_TOP}/embedded/platform/${PLATFORM}/cfe/cfe/include)
    bcm_module_header_paths(PUBLIC ${SOURCE_TOP}/embedded/platform/${PLATFORM}/cfe/cfe/arch/arm/common/include)
endif()

if(${BUF_IN_DMA_MEM})
    bcm_module_definitions(PUBLIC -DBCMOS_BUF_IN_DMA_MEM
                                  -DBCMOS_BUF_DATA_UNIT_SIZE=1024)
endif()

if("${OS}" STREQUAL "threadx" AND "${PLATFORM}" STREQUAL "aspen")
    bcm_make_debug_option(BUF_POOL_SIZE    STRING    "bcmos_buf system buffer pool size. 0=use heap" 1024)
elseif("${OS}" STREQUAL "threadx")
    bcm_make_debug_option(BUF_POOL_SIZE    STRING    "bcmos_buf system buffer pool size. 0=use heap" 512)
elseif("${SUBSYSTEM}" STREQUAL "embedded") # x86 simulation in embedded side
    bcm_make_debug_option(BUF_POOL_SIZE    STRING    "bcmos_buf system buffer pool size. 0=use heap" 1024)
else()
    bcm_make_debug_option(BUF_POOL_SIZE    STRING    "bcmos_buf system buffer pool size. 0=use heap" 0)
endif()

if(DEFINED BUF_POOL_SIZE AND NOT "${BUF_POOL_SIZE}" STREQUAL "0")
    if(NOT DEFINED BUF_POOL_BUF_SIZE)
        set(BUF_POOL_BUF_SIZE 4224)
    endif()
    if(NOT DEFINED BIG_BUF_POOL_SIZE)
        set(BIG_BUF_POOL_SIZE 16)
    endif()
    if(NOT DEFINED BIG_BUF_POOL_BUF_SIZE)
        set(BIG_BUF_POOL_BUF_SIZE 65536)
    endif()
    bcm_module_definitions(PUBLIC -DBCMOS_BUF_POOL_SIZE=${BUF_POOL_SIZE}
                                  -DBCMOS_BUF_POOL_BUF_SIZE=${BUF_POOL_BUF_SIZE}
                                  -DBCMOS_BIG_BUF_POOL_SIZE=${BIG_BUF_POOL_SIZE}
                                  -DBCMOS_BIG_BUF_POOL_BUF_SIZE=${BIG_BUF_POOL_BUF_SIZE})
endif()

if(${OS_HEAP_DEBUG})
    bcm_module_definitions(PUBLIC -DBCMOS_HEAP_DEBUG)
endif()

if(${OS_TIMER_DEBUG})
    bcm_module_definitions(PUBLIC -DBCMOS_TIMER_DEBUG)
endif()

if(${OS_BLK_POOL_DEBUG})
    bcm_module_definitions(PUBLIC -DBCMOS_BLK_POOL_DEBUG)
endif()

bcm_module_srcs(bcmos_common.c bcmos_errno.c bcmos_hash_table.c ${OS}/bcmos_system.c)

if(${COVERITY})
    bcm_module_srcs(bcmos_rw_lock_coverity.c)
else()
    bcm_module_srcs(bcmos_rw_lock.c)
endif()

if(${OS_MEM_CHECK})
    bcm_module_definitions(PUBLIC -DBCMOS_MEM_CHECK)
endif()

if(${ASPEN_PCIE_VLSI_SIM})
bcm_module_dependencies(PUBLIC pcie_dma_vlsi_sim_utils)
endif()

bcm_create_lib_target()

# Add additional subdirectories for this module
if(CLI AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/os_cli)
    bcm_add_subdirectory(os_cli)
endif()

if("${OS_KERNEL}" STREQUAL "linux")
    bcm_add_subdirectory(linux)
endif()

# Add files to the GitHub part of the release tree.
bcm_github_install(./*
    RELEASE github/os_abstraction
    EXCLUDE_FROM_RELEASE threadx vxworks55 cfe ipc_test linux os_cli unitest)
