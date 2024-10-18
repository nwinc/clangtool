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
By default, it will build with dynamic link. If you want a static build, please run
```
./build.sh --static

```
For more options, please check the build script for details.

## How to use
`clangtool` is a standalone command line tool, similar as offical LLVM tool `clang-check`.

`clangtool` can parse and analyze c/c++ source files via clang AST based on LLVM clang Tooling infrastructure.

An example using `clangtool` is integrated in `CMakeLists.txt`, it extracts function declarations in c/c++ header file, please check for more details.

This is only for demonstration, you can modify or extend as you want.
