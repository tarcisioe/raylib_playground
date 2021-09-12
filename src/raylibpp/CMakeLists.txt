add_library(raylibpp)

target_sources(
    raylibpp
        PUBLIC
            raylibpp.hpp
        PRIVATE
            raylib_utils.hpp
            raylib_utils.cpp
            raylibpp.cpp
)

target_include_directories(
    raylibpp
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    raylibpp
        PUBLIC
            canvas
            utility
            project_options
            CONAN_PKG::raylib
)

# add_subdirectory(tests)
