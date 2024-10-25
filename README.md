# Algoritmos eficientes para resolução de cubo mágico
Este projeto disponibiliza uma biblioteca para manipulação do cubo mágico, como:
* `Rubik.h`: funções para manipulação do cubo, como movimentação, embaralhamento, entre outros;
* `scores/Score.h`: funções e arquivos para implementação de pontuações para o cubo;
* `scores/Analyzer.h`: Analiza uma determinada configuração de uma pontuação, e diz o quanto ela é precisa;
* `solvers/Solver.h` funções e arquivos para implementação de solucionadores para o cubo;

# Dependências
* GCC versão 11 ou superior, para utilização de concepts (-std=c++20);
* libgomp instalada no G++ (openmp);
* CMake versão <strong>3.28</strong>;
* No projeto, o Makefile é utilizado como gerador, mas fique à vontade para usar qualquer uma suportada pelo CMake, basta alterar no arquivo `CMakePresets.json`;

# Exemplos
* Para ver os exemplos, vá na pasta /examples e execute o comando `cmake --preset examples .`. Esse comando irá compilar os exemplos na pasta /build/examples, você poderá executá-los por lá.

# Compilação
* Para executar algum código usando a biblioteca `librubik`, você deve escrever o código, e configurar corretamente no `CMakeLists.txt`, que deve conter as seguintes informações:

``` cmake
include("cmake/LinkRubikOpenMP.cmake") # Para usar target_link_rubik_and_openmp()
add_subdirectory(lib/rubik "${CMAKE_SOURCE_DIR}/build/lib/rubik") # Incluir a biblioteca

# Define as flags de compilação para Release e Debug
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(Teste main.cpp) # Criando o executável
target_link_rubik_and_openmp(Teste) # Linkando a biblioteca
```

* Os caminhos acima consideram a raiz do projeto, mude conforme necessário.

* Após configurar o cmake, pode-se executar o comando `cmake --preset [release|debug] .` para gerar o build, que será despejado na pasta /build/[release|debug]. Entrando nessa pasta, basta usar o comando `make` (ou o gerador configurado de sua preferência) e os executáveis serão gerados.