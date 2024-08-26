cmake_minimum_required(VERSION 3.5)

project(Rubik_Project)

# Adicionando subdiretorio da biblioteca rubik
add_subdirectory(lib/rubik)

# Executavel teste
add_executable(Teste main.cpp)

# Adicionando OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Teste PRIVATE OpenMP::OpenMP_CXX)
endif()

# Linkando biblioteca rubik
target_link_libraries(Teste PRIVATE rubik)