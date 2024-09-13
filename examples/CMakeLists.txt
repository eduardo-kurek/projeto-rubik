cmake_minimum_required(VERSION 3.5)

project(Rubik_Examples)
include("../cmake/LinkRubikOpenMP.cmake")
add_subdirectory("../lib/rubik" "${CMAKE_BINARY_DIR}/../lib/rubik")

add_executable(Rubik rubik_example.cpp)
target_link_rubik_and_openmp(Rubik)

add_executable(Score score_example.cpp)
target_link_rubik_and_openmp(Score)