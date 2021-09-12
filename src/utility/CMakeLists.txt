
add_library(utility)

target_sources(
    utility
        PUBLIC
            move.hpp
        PRIVATE
            move.cpp
)

target_include_directories(
    utility
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    utility
        PUBLIC
            project_options
)
