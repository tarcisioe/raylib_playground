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
