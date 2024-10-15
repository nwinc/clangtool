# clangtool
A simple clang tool for demonstration based on LLVM clang Tooling infrastructure

## Prerequisites
* cmake (version > 3.20)
* ninja
* clang

## Build
Please run following command to build
```
./build.sh
```
For more options for building, please check build script for details.

## How to use
`clangtool` is a standalone command line tool, similar as offical LLVM tool `clang-check`.

`clangtool` can parse and analyze c/c++ source files via clang AST based on LLVM clang Tooling infrastructure.

An example using `clangtool` is integrated in `CMakeLists.txt`, it extracts function declarationsin c/c++ header file, please check for more details.

This is only for demonstration, you can modify or extend as you want.
