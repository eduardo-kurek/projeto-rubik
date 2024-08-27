cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(RubikExample rubik_example.cpp)
add_subdirectory(../lib/rubik ${CMAKE_SOURCE_DIR}/../build/lib/rubik)
target_link_libraries(RubikExample PRIVATE rubik)

# Adicionando OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(RubikExample PRIVATE OpenMP::OpenMP_CXX)
endif()