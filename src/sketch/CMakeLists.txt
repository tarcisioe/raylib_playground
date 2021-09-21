add_library(sketch)

target_sources(
    canvas
        PUBLIC
            sketch.hpp
        PRIVATE
            sketch.cpp
)

target_include_directories(
    sketch
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    sketch
        PUBLIC
            project_options
            canvas
)

# add_subdirectory(tests)
