cmake_minimum_required(VERSION 3.15)
project(raylib_playground CXX)

include(cmake/base.cmake)
include(cmake/project_options.cmake)
include(cmake/conan.cmake)

conan(
    PACKAGES
        raylib/3.5.0
)

add_subdirectory(src)
