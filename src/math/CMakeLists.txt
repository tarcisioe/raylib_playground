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
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    math
        PUBLIC
            project_options
)
