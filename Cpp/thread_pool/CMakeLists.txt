cmake_minimum_required(VERSION 3.0)

project(thread_pool)

add_executable(thread_pool example.cpp)

target_include_directories(thread_pool
    PRIVATE
    ./
)

target_link_libraries(thread_pool pthread)