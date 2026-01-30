cmake_minimum_required(VERSION 3.31)
project(noalloc)

set(CMAKE_CXX_STANDARD 20)

add_executable(basic examples/basic.cpp
        noalloc.h
        noalloc.cpp
)

add_executable(nested examples/nested.cpp
        noalloc.h
        noalloc.cpp
)
