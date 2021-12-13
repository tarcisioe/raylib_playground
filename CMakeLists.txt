cmake_minimum_required(VERSION 3.15)
project(raylib_playground CXX)

include(cmake/base.cmake)
include(cmake/project_options.cmake)
include(cmake/conan.cmake)
include(cmake/catch2.cmake)

enable_testing()

conan(
    PACKAGES
        catch2/2.13.7
        raylib/3.5.0
        range-v3/0.11.0
        fmt/8.0.1
)

add_subdirectory(src)
