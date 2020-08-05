cmake_minimum_required(VERSION 3.10)
project(argarse)

set(CMAKE_C_COMPILER /usr/bin/gcc-8)
set(CMAKE_CXX_COMPILER /usr/bin/g++-8)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${PROJECT_SOURCE_DIR}/
)
