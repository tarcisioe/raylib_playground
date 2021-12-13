add_library(math)

target_sources(
    math
        PUBLIC
            geom/bezier.hpp
            geom/matrix.hpp
            geom/vec2.hpp
            geom/vec3.hpp
        PRIVATE
            geom/bezier.cpp
            geom/matrix.cpp
            geom/vec2.cpp
            geom/vec3.cpp
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
