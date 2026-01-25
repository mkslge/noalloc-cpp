cmake_minimum_required(VERSION 3.31)
project(noalloc)

set(CMAKE_CXX_STANDARD 20)

add_executable(noalloc examples/main.cpp
        noalloc.h
        noalloc.cpp)
