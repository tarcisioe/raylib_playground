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
            canvas
            math
            raylibpp_runner
            sketch
            CONAN_PKG::range-v3
)
