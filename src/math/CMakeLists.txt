add_library(math)

target_sources(
    math
        PUBLIC
            geom/bezier.hpp
            geom/vec2.hpp
        PRIVATE
            geom/bezier.cpp
            geom/vec2.cpp
)

target_include_directories(
    math
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    math
        PUBLIC
            project_options
)

add_subdirectory(tests)
