add_executable(fourier)

target_sources(
    fourier
        PRIVATE
            fourier.cpp
)

target_link_libraries(
    fourier
        PRIVATE
            canvas
            math
            raylibpp
            CONAN_PKG::range-v3
)
