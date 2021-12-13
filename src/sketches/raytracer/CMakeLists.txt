add_executable(raytracer)

target_sources(
    raytracer
        PRIVATE
            raytracer.cpp
)

target_link_libraries(
    raytracer
        PRIVATE
            raylibpp_runner
            sketch
            CONAN_PKG::fmt
)
