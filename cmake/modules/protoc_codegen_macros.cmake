# This file contains macros for code generation using protobuf protoc

#==============
# Global variables defined when this file gets included to the top level CMakeLists.txt
#==============
set(BCM_PROTOGEN_LICENSE_PATH   ${SOURCE_TOP}/codegen/license.txt)

#==============
# PRIVATE: Clear all local variables after using them.
#==============
macro(_bcm_module_protoc_clear)
    unset(_MOD_GEN_SRCS)
    unset(_MOD_GEN_HDRS)
endmacro(_bcm_module_protoc_clear)

#==============
# Add source files to be generated. Entries are appended to the running list. Global _MOD_GEN_SRCS is used
# for storage.
# @param ARGN           [in] Sources to append to the running list
#==============
macro(bcm_module_protoc_srcs)
    list(APPEND _MOD_GEN_SRCS ${ARGN})
    string(REPLACE .cc .h _hdrs ${ARGN})
    list(APPEND _MOD_GEN_HDRS ${hdrs})
endmacro(bcm_module_protoc_srcs)

#==============
# Run the protoc code generator.
#
# _MOD_GEN_SRCS: .c files to generate.
#
# All output files must have a corresponding file with extension .proto in the source directory.
#==============
macro(bcm_protoc_generate)
    set(OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

    unset(OUTPUTS)
    unset(_PROTOC)
    unset(_GRPC_PLUGIN)

    # Check that protoc and grpc_cpp_plugic are installed
    # When building on x86, protoc is one of the artifacts of imported grpc module.
    # When cross-compiling, protoc must be pre-installed
    # ToDo: deal with multiple protoc version on the build server
    if(BCM_CONFIG_HOST MATCHES "x86")
        set(_PROTOC ${BUILD_TOP}/fs/bin/protoc)
    else()
        if(EXISTS ${BUILD_TOP}/../host-sim/fs/bin/protoc)
            set(_PROTOC ${BUILD_TOP}/../host-sim/fs/bin/protoc)
        elseif(PROTOC_PATH)
            find_program(_PROTOC protoc PATHS ${PROTOC_PATH})
        else()
            find_program(_PROTOC protoc)
        endif()
        if(NOT _PROTOC)
            message(FATAL_ERROR "protoc is not found. Can't generate C++ code from .proto files")
        endif()
    endif()
    get_filename_component(_PROTOC_DIR ${_PROTOC} DIRECTORY)
    set(_GRPC_PLUGIN ${_PROTOC_DIR}/grpc_cpp_plugin)
    if(NOT (BCM_CONFIG_HOST MATCHES "x86"))
        find_program(_GRPC_PLUGIN ${_GRPC_PLUGIN})
        if(NOT _GRPC_PLUGIN)
            message(FATAL_ERROR "${_GRPC_PLUGIN} is not found. Can't generate C++ grpc stubs from .proto files")
        endif()
    endif()
    set(_SHLIB_PATH ${_PROTOC_DIR}/../lib)

    set(_PROTOGEN_RULE LD_LIBRARY_PATH=${_SHLIB_PATH} ${_PROTOC} -I${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${OUT_DIR})
    set(_GRPCGEN_RULE LD_LIBRARY_PATH=${_SHLIB_PATH} ${_PROTOC} -I${CMAKE_CURRENT_SOURCE_DIR} --grpc_out=${OUT_DIR} --plugin=protoc-gen-grpc=${_GRPC_PLUGIN})

    # Export the output directory as an include path.
    bcm_module_header_paths(PUBLIC ${OUT_DIR})

    foreach(_FILENAME ${_MOD_GEN_SRCS})
        bcm_module_srcs("${OUT_DIR}/${_FILENAME}")
    endforeach(_FILENAME)

    # This path we generate the files, otherwise we've already added the pre-existing files before we got here.
    set(TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

    foreach(_FILENAME ${_MOD_GEN_SRCS})
        bcm_module_srcs("${OUT_DIR}/${_FILENAME}")
    endforeach(_FILENAME)

    foreach(_FILENAME ${_MOD_GEN_SRCS})
        # Generate protobuf or grpc classes, depending on file extension
        if(${_FILENAME} MATCHES ".*\.grpc\.pb\.cc")
            set(_RULE ${_GRPCGEN_RULE})
            string(REPLACE ".grpc.pb.cc" ".proto" _PROTOFILE ${_FILENAME})
        elseif(${_FILENAME} MATCHES ".*\.pb\.cc")
            set(_RULE ${_PROTOGEN_RULE})
            string(REPLACE ".pb.cc" ".proto" _PROTOFILE ${_FILENAME})
        else()
            message(FATAL_ERROR "Filename must be in format name.pb.cc or name.grpc.pb.cc: ${_FILENAME}")
        endif()
        string(REPLACE ".pb.cc" ".pb.h" _HDRNAME ${_FILENAME})

        list(APPEND OUTPUTS ${OUT_DIR}/${_FILENAME})
        list(APPEND OUTPUTS ${OUT_DIR}/${_HDRNAME})

        # Add target for .cc generation
        add_custom_command(OUTPUT ${OUT_DIR}/${_FILENAME} ${OUT_DIR}/${_HDRNAME}
                            COMMAND echo "Generating files ${_FILENAME}, ${_HDRNAME} in ${OUT_DIR}..."
                            COMMAND mkdir -p ${OUT_DIR}
                            COMMAND ${_RULE} ${CMAKE_CURRENT_SOURCE_DIR}/${_PROTOFILE}
                            VERBATIM
                            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_PROTOFILE} grpc)
    endforeach(_FILENAME)

    # Set the build global with the output files
    bcm_module_codegen_output(${OUTPUTS})

    _bcm_module_protoc_clear()
endmacro(bcm_protoc_generate)
