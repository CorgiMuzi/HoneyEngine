cmake_minimum_required(VERSION 4.0)
project(HoneyEngine)

if (MSVC)
    add_compile_options("/utf-8")
endif ()

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
