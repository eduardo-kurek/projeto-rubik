cmake_minimum_required(VERSION 3.28)

add_library(rubik STATIC)

# É necessário compilar com C++20 devido uso de <concepts>
target_compile_features(rubik PUBLIC cxx_std_20)
target_include_directories(rubik PUBLIC "include/")
file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(rubik PRIVATE ${SOURCES})