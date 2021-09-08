add_library(raylibpp)

target_sources(
    raylibpp
        PUBLIC
            raylibpp.hpp
        PRIVATE
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
            project_options
            CONAN_PKG::raylib
)

# add_subdirectory(tests)
