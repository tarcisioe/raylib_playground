add_library(test_common)

target_sources(
    test_common
        PRIVATE
            test_main.cpp
)

target_include_directories(
    test_common
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    test_common
        PUBLIC
            project_options
            CONAN_PKG::catch2
)
