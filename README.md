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

## Compilação
* 