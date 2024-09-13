cmake_minimum_required(VERSION 3.5)

project(Rubik_Project)

# Define as flags de compilação para Release e Debug
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Executaveis do projeto
add_executable(Teste main.cpp)

# Linkando biblioteca rubik
# set(RUBIK_LIB_DIR "${CMAKE_SOURCE_DIR}/build/lib/rubik")
# target_link_libraries(Teste PRIVATE "${RUBIK_LIB_DIR}/librubik.a")
# target_include_directories(Teste PRIVATE "${CMAKE_SOURCE_DIR}/lib/rubik/include")

add_subdirectory(lib/rubik "${CMAKE_SOURCE_DIR}/build/lib/rubik")

target_link_libraries(Teste PRIVATE rubik)

# Adicionando OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Teste PRIVATE OpenMP::OpenMP_CXX)
endif()

