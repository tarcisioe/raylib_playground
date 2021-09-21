add_library(canvas)

target_sources(
    canvas
        PUBLIC
            canvas.hpp
        PRIVATE
            canvas.cpp
)

target_include_directories(
    canvas
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    canvas
        PUBLIC
            project_options
            color
            math
)

# add_subdirectory(tests)
