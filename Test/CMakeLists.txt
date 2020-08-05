cmake_minimum_required(VERSION 3.0)

project(test)

add_executable(test test.cpp)

target_link_libraries(test pthread)