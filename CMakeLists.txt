
cmake_minimum_required(VERSION 3.16)
project(fractals C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find raylib (Homebrew installs a proper CMake config)
find_package(raylib REQUIRED)

add_executable(mandelbrot
    mandelbrot.c
)

target_link_libraries(mandelbrot
    raylib
)

# macOS specific frameworks raylib depends on
if (APPLE)
    target_link_libraries(mandelbrot
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
        "-framework CoreVideo"
    )
endif()
