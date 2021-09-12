add_executable(main)

target_sources(
    main
        PRIVATE
            main.cpp
)

target_link_libraries(
    main
        PRIVATE
            math
            project_options
            CONAN_PKG::raylib
)

add_executable(testing_grounds)

target_sources(
    testing_grounds
        PRIVATE
            testing_grounds.cpp
)

target_link_libraries(
    testing_grounds
        PRIVATE
            canvas
            math
            raylibpp
)

add_subdirectory(fourier)
