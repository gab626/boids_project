cmake_minimum_required(VERSION 3.16)
project(BoidsProject VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

find_package(SFML COMPONENTS system window graphics REQUIRED)
# find_package(TGUI REQUIRED)

add_executable(BoidsProject src/boid.cpp src/grid.cpp src/functions.cpp src/flock.cpp src/simulation.cpp src/main.cpp)

target_link_libraries(BoidsProject PRIVATE sfml-system sfml-window sfml-graphics)

if (WIN32)
    target_link_libraries(BoidsProject PRIVATE sfml-main)
endif()

# Debugging output
message(STATUS "CMake CXX Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMake CXX Debug Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMake Exe Linker Debug Flags: ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")

# if (BUILD_TESTING)

# ...

# endif()