# CMake

## 内置变量

`message($(xxx))` 可以查看变量的内容

| Variable |Info|
|--|--|
|PROJECT_NAME|project(xxx) 中的 xxx
|CMAKE_SOURCE_DIR | The root source directory
|CMAKE_CURRENT_SOURCE_DIR |The current source directory if using sub-projects and directories.
|PROJECT_SOURCE_DIR | 源代码所在目录, 一般在 build 目录的上一级, The source directory of the current cmake project.
|CMAKE_BINARY_DIR | build 所在目录, The root binary / build directory. This is the directory where you ran the cmake command.
|CMAKE_CURRENT_BINARY_DIR |The build directory you are currently in.
|PROJECT_BINARY_DIR |The build directory for the current project.

## [CMake 两种变量原理 Normal Variables、Cache Variables](https://www.cnblogs.com/ncuneugcj/p/9756324.html)

## 创建源文件变量

```cmake
add_executable(${PROJECT_NAME}
    src/Hello.cpp
    src/main.cpp
)

# 也可以将source文件赋值给一个变量

set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
```

## 包含头文件

```cmake
include_directories(${PROJECT_SOURCE_DIR}/include)

#### 也可以

target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
```

## make

- `make clean` 清除上次编译结果
- `make VERBOSE=1` 将编译过程打印出来

## 生成动态/静态库

```cmake
add_library(hello_library STATIC
    src/Hello.cpp
)

add_library(hello_library SHARED
    src/Hello.cpp
)
```

## 安装与卸载

- 安装命令 `sudo make install`
- 默认情况下, 会安装到 `/usr/local` 目录下, 也可以通过 `cmake .. -DCMAKE_INSTALL_PREFIX=/install/location` 来指定安装目录  
- 安装细节会保存在 `./build/install_manifest.txt` 文件中, 如要卸载, 可以直接将该文件中的对应文件删除, 例如 `cat install_manifest.txt | xargs -p sudo rm`

```cmake
# Binaries
install (TARGETS cmake_examples_inst_bin
    DESTINATION bin)

# Library
# Note: may not work on windows
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include)

# Config
install (FILES cmake-examples.conf
    DESTINATION etc)
```

## [`CMAKE_C_FLAGS` 和 `CMAKE_CXX_FLAGS`](https://blog.csdn.net/QTVLC/article/details/82965398)

Once set the CMAKE_C_FLAGS and CMAKE_CXX_FLAGS will set a compiler flag / definition globally for all targets in this directory or any included sub-directories. This method is not recommended for general usage now and **the target_compile_definitions function is preferred**

## `find_package()`

This will search for CMake modules in the format "FindXXX.cmake" from the list of folders in `CMAKE_MODULE_PATH`. On linux the default search path will include `/usr/share/cmake/Modules`

A basic example of finding boost is below:  
`find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)`
The arguments are:

- Boost - Name of the library. This is part of used to find the module file FindBoost.cmake
- 1.46.1 - The minimum version of boost to find
- REQUIRED - Tells the module that this is required and to fail it it cannot be found
- COMPONENTS - The list of libraries to find.

## Ninja

Ninja 是Google的一名程序员推出的注重速度的构建工具，一般在Unix/Linux上的程序通过make/makefile来构建编译，而Ninja通过将编译任务并行组织，大大提高了构建速度。

- `sudo apt install ninja-build` # 安装
- 使用

```sh
cmake .. -G Ninja
ninja
```
