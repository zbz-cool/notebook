cmake_minimum_required(VERSION 3.0)

project(test)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(test test.cpp)

target_link_libraries(test pthread)