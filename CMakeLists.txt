cmake_minimum_required(VERSION 3.20.0)

project(clang-tool)

set(TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(OUTPUT_DIR ${CMAKE_BINARY_DIR})

set(CLANGTOOL_EXECUTABLE clangtool)
set(CLANGTOOL_SOURCES clangtool.cpp)

set(LLVM_ROOT_PATH ${TOP_DIR}/llvm-project)
set(INTRIN_DEF_FILE_INSTALL_DIR ${LLVM_ROOT_PATH}/clang/include/clang/Basic)
set(INTRIN_INC_FILE_INSTALL_DIR ${LLVM_ROOT_PATH}/clang/include/clang/Basic)
set(INTRIN_TD_FILE_INSTALL_DIR ${LLVM_ROOT_PATH}/llvm/include/llvm/IR)
set(INTRIN_HEADER_FILE ${TOP_DIR}/example/cpu0_intrinsic.h)
set(GEN_INTRIN_DEF_FILE BuiltinsCpu0.def)
set(GEN_INTRIN_INC_FILE Cpu0GenIntrinsicBuiltinsCG.inc)
set(GEN_INTRIN_TD_FILE IntrinsicsCpu0.td)

# set(CMAKE_VERBOSE_MAKEFILE "ON")

option(LANGUAGE_MODE_CXX "Processing as C++ source, disabled by default" OFF)
if (LANGUAGE_MODE_CXX)
    set(LANGUAGE_OPTION "-xc++")
else()
    set(LANGUAGE_OPTION "-xc")
endif()

option(ENABLE_STATIC_BUILD "Building with static LLVM libraries, disabled by default" OFF)
if (ENABLE_STATIC_BUILD)
    set(OPT_STATIC "--static")
endif()

set(CMAKE_CXX_FLAGS "-std=c++17")

find_library(LIBCLANG "clang" PATHS ${TOP_DIR}/build_libclang/install/lib NO_DEFAULT_PATH)
if (LIBCLANG)
    get_filename_component(LIBCLANG_DIR ${LIBCLANG} DIRECTORY)
    message("find libclang in ${LIBCLANG_DIR}")
    set(LIBCLANG_INSTALL_BASE_DIR ${LIBCLANG_DIR}/..)
else()
    message("libclang not found, need to rebuild")
    add_custom_target(
        build_libclang
        COMMAND ${TOP_DIR}/build.sh --llvm ${OPT_STATIC}
        WORKING_DIRECTORY ${TOP_DIR}
        COMMENT "Building libclang")
    set(LIBCLANG_INSTALL_BASE_DIR ${TOP_DIR}/build_libclang/install)
endif()

string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)
if(uppercase_CMAKE_BUILD_TYPE STREQUAL "DEBUG" )
  add_definitions(-DDEBUG)
endif()

include_directories(${LIBCLANG_INSTALL_BASE_DIR}/include)
link_directories(${LIBCLANG_INSTALL_BASE_DIR}/lib)
add_compile_options(-fno-rtti)

add_executable(${CLANGTOOL_EXECUTABLE} ${CLANGTOOL_SOURCES})
if (NOT ENABLE_STATIC_BUILD)
    target_link_libraries(${CLANGTOOL_EXECUTABLE} clang clang-cpp LLVM)
else()
    target_link_libraries(${CLANGTOOL_EXECUTABLE}
        PRIVATE
        LLVMX86CodeGen
        LLVMX86AsmParser
        LLVMX86Desc
        LLVMX86Disassembler
        LLVMX86Info
        clangAST
        clangBasic
        clangDriver
        clangFrontend
        clangRewriteFrontend
        clangSerialization
        clangStaticAnalyzerFrontend
        clangTooling
        clangToolingSyntax

        LLVMAsmPrinter
        LLVMCFGuard
        LLVMGlobalISel
        LLVMIRPrinter
        LLVMInstrumentation
        LLVMSelectionDAG
        LLVMCodeGen
        LLVMBitWriter
        LLVMObjCARCOpts
        LLVMTarget
        LLVMCodeGenTypes
        LLVMMCDisassembler
        clangStaticAnalyzerCheckers
        clangStaticAnalyzerCore
        clangCrossTU
        clangIndex
        clangFormat
        clangToolingInclusions
        clangFrontend
        clangDriver
        LLVMWindowsDriver
        LLVMOption
        clangSerialization
        clangParse
        clangSema
        clangAPINotes
        clangEdit
        clangAnalysis
        clangASTMatchers
        clangAST
        clangSupport
        LLVMFrontendHLSL
        clangToolingCore
        clangRewrite
        clangLex
        clangBasic
        LLVMFrontendOpenMP
        LLVMScalarOpts
        LLVMAggressiveInstCombine
        LLVMInstCombine
        LLVMFrontendOffloading
        LLVMTransformUtils
        LLVMAnalysis
        LLVMProfileData
        LLVMSymbolize
        LLVMDebugInfoDWARF
        LLVMDebugInfoPDB
        LLVMDebugInfoMSF
        LLVMDebugInfoBTF
        LLVMObject
        LLVMMCParser
        LLVMMC
        LLVMDebugInfoCodeView
        LLVMIRReader
        LLVMBitReader
        LLVMAsmParser
        LLVMTextAPI
        LLVMCore
        LLVMRemarks
        LLVMBitstreamReader
        LLVMBinaryFormat
        LLVMTargetParser
        LLVMSupport
        LLVMDemangle

        rt
        dl
        pthread
        z
        tinfo)
endif()

if (NOT LIBCLANG)
    add_dependencies(${CLANGTOOL_EXECUTABLE} build_libclang)
endif()


set(LIBCLANG_BUILD_DIR ${TOP_DIR}/build_libclang)
set(EXTRA_INCLUDE_DIR ${LIBCLANG_INSTALL_BASE_DIR}/lib/clang/18/include)

add_custom_command(TARGET ${CLANGTOOL_EXECUTABLE}
    POST_BUILD
    COMMAND ${CLANGTOOL_EXECUTABLE} -p ${LIBCLANG_BUILD_DIR} --extra-arg-before=--target=riscv32
                ${INTRIN_HEADER_FILE} -- -I ${EXTRA_INCLUDE_DIR} ${LANGUAGE_OPTION}
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GEN_INTRIN_DEF_FILE} ${INTRIN_DEF_FILE_INSTALL_DIR}/${GEN_INTRIN_DEF_FILE}
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GEN_INTRIN_INC_FILE} ${INTRIN_INC_FILE_INSTALL_DIR}/${GEN_INTRIN_INC_FILE}
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GEN_INTRIN_TD_FILE} ${INTRIN_TD_FILE_INSTALL_DIR}/${GEN_INTRIN_TD_FILE}
    COMMENT "${CLANGTOOL_EXECUTABLE}: Generating intrinsic files")
