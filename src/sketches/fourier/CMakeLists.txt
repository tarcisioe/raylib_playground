add_executable(fourier)

target_sources(
    fourier
        PRIVATE
            epicycles.hpp
            epicycles.cpp
            fourier.cpp
)

target_link_libraries(
    fourier
        PRIVATE
            raylibpp_runner
            sketch
            CONAN_PKG::range-v3
)

add_executable(fourier2d)

target_sources(
    fourier2d
        PRIVATE
            epicycles.hpp
            epicycles.cpp
            fourier2d.cpp
)

target_link_libraries(
    fourier2d
        PRIVATE
            raylibpp_runner
            sketch
            CONAN_PKG::range-v3
)
