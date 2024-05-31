# Algoritmos eficientes para resolução de cubo mágico
Funções disponíveis até o momento podem ser encontradas no arquivo rubik/rubik.h. Incluem: criação, destruição, movimentação, embaralhamento, importação, exportação entre outros
<br><br>

### Dependências
* GCC versão 8, para utilização da bilioteca *filesystem*.
* Makefile, para construção do projeto.

#### Compilação
* Para compilar todo o código fonte, basta digitar `make all` em um terminal com a raiz do projeto. Todos os executáveis gerados ficaram
na pasta /bin, e o código-objeto na pasta /obj. Para usar a API do cubo mágico como quiser, o código poderá ser escrito em qualquer lugar e
os cabeçalhos deveram ser inclusos corretamente. Depois é só digitar `make bin/caminho/do/código`, considerando o caminho relativo da raiz do projeto.
Se o arquivo .cpp estiver em uma pasta criada manualmente, deverá ser adicionado o diretório com o préfixo *bin/* na regra `make dir`.