cmake_minimum_required(VERSION 3.5)

project(Rubik_Project)
include("cmake/LinkRubikOpenMP.cmake")
add_subdirectory(lib/rubik "${CMAKE_SOURCE_DIR}/build/lib/rubik")

# Define as flags de compilação para Release e Debug
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(Teste main.cpp)
target_link_rubik_and_openmp(Teste)