cmake_minimum_required(VERSION 4.0)
project(HoneyEngine)

if (MSVC)
    add_compile_options("/utf-8")
endif ()

set(CMAKE_CXX_STANDARD 23)

set(SDLIMAGE_AVIF OFF CACHE BOOL "Disable AVIF support" FORCE)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/glm)

add_subdirectory(src)
