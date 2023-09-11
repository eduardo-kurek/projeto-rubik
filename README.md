# Algoritmos eficientes para resolução de cubo mágico
Funções disponíveis até o momento podem ser encontradas no arquivo rubik/rubik.h. Incluem: criação, destruição, movimentação, embaralhamento, importação, exportação entre outros. Estas funções podem ser chamadas em qualquer arquivo, basta incluir o cabeçalho da biblioteca e adicionar o executavel _rubik.o_ ao parâmetro de compilação.
<br><br>

#### O arquivo makefile possui alguns atalhos para compilação:
* **Variáveis:** é preciso definir algumas váriaveis de acordo com o terminal do usuário, para que os comandos funcionem corretamente. As primeiras linhas servem para isso, identificar se o terminal é linux ou windows, e resolver a diferença de comandos entre os dois (pode não funcionar corretamente);
* O alvo **"compile"** é responsável por compilar as bibliotecas dentro de rubik/;
* O alvo **"all"** chama o alvo compile, e logo após isso, executa o arquivo main.c;
* O alvo **"test"** chama o alvo compile, e logo após isso, executa o arquivo testes.c, caso exista na raiz;

#### Exemplos de usos: (main.c)

```c
#include <stdio.h>
#include "rubik/rubik.h"

int main(){
    Rubik* rubik = rubik_criar();
    char* embaralhamento = rubik_embaralhar(rubik, 20);
    rubik_movimentar(rubik, 1, F);
    
    rubik_imprimir(rubik);
    char* exportacao = rubik_exportar(rubik);
    
    printf("Embaralhamento realizado: %s\n", embaralhamento);
    printf("Cubo exportado em string: %s\n", exportacao);
    
    Rubik* copia = rubik_importar(exportacao);
    printf("Copia do primeiro cubo: \n");
    rubik_imprimir(copia);
    
    rubik_destruir(&rubik);
    rubik_destruir(&copia);
    
    return 0;
}
```

### O makefile deste código para execução deste código deve ficar desta maneira:
```makefile
ifeq ($(TERM), xterm-256color)
    OUT=a.out
    CLEAN=rm
    CLEAR=clear
else
    OUT=a.exe
    CLEAN=del
    CLEAR=cls
endif

all:
    make compile
    gcc main.c "rubik/rubik.o" -o $(OUT)
    $(CLEAR)
    ./$(OUT)
    
compile:
    gcc -c "rubik/rubik.c" -o "rubik/rubik.o"
```