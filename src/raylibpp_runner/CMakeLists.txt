add_library(raylibpp_runner)

target_sources(
    raylibpp_runner
        PUBLIC
            runner.hpp
        PRIVATE
            runner.cpp
)

target_include_directories(
    raylibpp_runner
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    raylibpp_runner
        PUBLIC
            project_options
            sketch
            raylibpp
)

# add_subdirectory(tests)
