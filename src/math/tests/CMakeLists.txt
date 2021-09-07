add_executable(test_geom)

target_sources(
    test_geom
        PRIVATE
            test_geom/test_vec2.cpp
)

target_link_libraries(
    test_geom
        PRIVATE
            math
            test_common
            project_options
)

add_catch2_test(test_geom)
