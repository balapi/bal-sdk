# Add any optional cmake macros we use for internal testing

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/external_import.cmake)
    include(external_import)
endif()
