#!/bin/bash

BUILD_DIR=build
BUILD_LIBCLANG_DIR=build_libclang
LLVM_SOURCE_DIR=llvm-project
CLANG_TOOL=clangtool

build_help()
{
        echo -e "\nusage: $0 [options]\n"

        echo -e "options:\n"
        echo -e "  -llvm,  --llvm              Build llvm project only and exit"
        echo -e "  -static,  --static          Enable static build, disabled by default."
        echo -e "  -cxx,  --cxx                Source language is C++, default C."
        echo -e "  -h,  --help                 Prints this help"
}

build_llvm()
{
    local BUILD_DIR="$1"

    if [ -d "$BUILD_DIR" ]; then
        ninja -C $BUILD_DIR install
    else
        if [ "$ENABLE_STATIC" = "yes" ]; then
            cmake -G "Ninja" \
                -S ${LLVM_SOURCE_DIR}/llvm \
                -B $BUILD_DIR \
                -DLLVM_ENABLE_PROJECTS="clang" \
                -DCMAKE_BUILD_TYPE=Release \
                -DLLVM_TARGETS_TO_BUILD="X86" \
                -DCMAKE_CXX_COMPILER=clang++ \
                -DCMAKE_C_COMPILER=clang \
                -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
                -DCMAKE_INSTALL_PREFIX=${BUILD_DIR}/install
        else
            cmake -G "Ninja" \
                -S ${LLVM_SOURCE_DIR}/llvm \
                -B $BUILD_DIR \
                -DLLVM_ENABLE_PROJECTS="clang" \
                -DCMAKE_BUILD_TYPE=Release \
                -DLLVM_TARGETS_TO_BUILD="X86" \
                -DCMAKE_CXX_COMPILER=clang++ \
                -DCMAKE_C_COMPILER=clang \
                -DLLVM_BUILD_LLVM_DYLIB=ON \
                -DLLVM_LINK_LLVM_DYLIB=ON \
                -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
                -DCMAKE_INSTALL_PREFIX=${BUILD_DIR}/install
        fi
        ninja -C $BUILD_DIR install
    fi
}

do_build()
{
    local BUILD_OPTIONS="-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++"

    if [ "$BUILD_LLVM" = "yes" ]; then
        build_llvm $BUILD_LIBCLANG_DIR
        exit 0
    fi

    rm -rf $BUILD_DIR

    if [ "$ENABLE_CXX" = "yes" ]; then
        BUILD_OPTIONS="$BUILD_OPTIONS -DLANGUAGE_MODE_CXX=ON"
    fi
    if [ "$ENABLE_STATIC" = "yes" ]; then
        BUILD_OPTIONS="$BUILD_OPTIONS -DENABLE_STATIC_BUILD=ON"
    fi

    cmake -B $BUILD_DIR ${BUILD_OPTIONS}

    make -C $BUILD_DIR $CLANG_TOOL
}

while [ -n "$1" ];
do
    case $1 in
    -h  | --help )
        build_help
        exit 1
        ;;
    -llvm  | --llvm )
        BUILD_LLVM="yes"
        ;;
    -cxx  | --cxx )
        ENABLE_CXX="yes"
        ;;
    -static  | --static )
        ENABLE_STATIC="yes"
        ;;
    *)
        echo "The parameter $1 is not allowed"
        build_help
        exit 1
        ;;
    esac
    shift
done

do_build
