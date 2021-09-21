add_library(color)

target_sources(
    color
        PUBLIC
            color.hpp
        PRIVATE
            color.cpp
)

target_include_directories(
    color
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    color
        PUBLIC
            project_options
)

# add_subdirectory(tests)
