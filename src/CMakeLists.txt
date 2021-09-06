add_executable(main)

add_subdirectory(math)

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
