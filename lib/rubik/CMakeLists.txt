cmake_minimum_required(VERSION 3.5)

# Definir o diretório de saída dos executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")

# Define a biblioteca rubik
add_library(rubik STATIC)

# É necessário compilar com C++20 devido uso de <concepts>
target_compile_features(rubik PUBLIC cxx_std_20)

# Adicionando os arquivos de cabeçalho e fontes
target_include_directories(rubik PUBLIC "include/")
file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(rubik PUBLIC ${SOURCES})

# Adicionando o OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(rubik PUBLIC OpenMP::OpenMP_CXX)
endif()