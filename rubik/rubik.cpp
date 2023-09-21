#include "rubik.h"
#include <time.h>

/**************************************************************
* ESTRUTURAS
**************************************************************/
#pragma region ESTRUTURAS
    /**************************************************************
     * @note char nome: nome da cor
     * @note int cod: código referente a cor, 1 à 6
     * @note char ch[15]: string referente ao codigo de impressão da cor
    **************************************************************/
    struct cor{
        char nome[10];
        char cod;
        char ch[25];
    };

    /**************************************************************
     * @note const Cor* cor: objeto 'Cor' que o adesivo está atrelado
    **************************************************************/
    struct adesivo{
        const struct cor* cor;
    };

    /**************************************************************
    * @note Adesivo* adesivos[3][3]: matriz contendo os adesivos da face
    **************************************************************/
    struct face{
        struct adesivo* adesivos[3][3];
    };

    /**************************************************************
    * @note const short int ci: começo do índice 'i'
    * @note const short int ti: término do índice 'i'
    * @note const short int cj: começo do índice 'j'
    * @note const short int tj: término do índice 'j'
    **************************************************************/
    struct camada{
        const short int ci;
        const short int ti;
        const short int cj;
        const short int tj;
    };


    /**************************************************************
    * @note const short int faces[4]: as quatro faces que serão giradas
    * @note const Camada* camadas[4]: refere qual a camada de determi-
    *  nada face deve ser movida
    * @note const short int faceFraca: qual face deve ser apenas girada
    *  (-1) para nenhuma face
    * @note const short int sentido: qual o sentido a face fraca rodará
    *  horário (0) ou anti-horário (1)
    *  short int quantidade: quantidade de vezes que o movimento
    *  repetirá
    *  short int indice: indice que mapeia o movimento
    **************************************************************/
    struct movimento{
        const short int faces[4];
        const struct camada* camadas[4];
        const short int faceFraca;
        const short int sentido;
        short int quantidade;
        short int indice;
        char nome[3];
    };

    struct no{
        const Movimento* dado;
        struct no *ant;
        struct no *prox;
    };

    /**************************************************************
     * Objeto referente a um nó do histórico
     **************************************************************/
    struct historico{
        struct no *sentinela;
        int qtde;
    };

    /**************************************************************
    * @note Face* 0: objeto 'Face' referente a face frontal
    * @note Face* 1: objeto 'Face' referente a face superior
    * @note Face* 2: objeto 'Face' referente a face lateral dir.
    * @note Face* 3: objeto 'Face' referente a face inferior
    * @note Face* 4: objeto 'Face' referente a face lateral esq.
    * @note Face* 5: objeto 'Face' referente a face posterior
    * @note const Movimento* ultimo: Ultimo movimento realizado no cubo
    **************************************************************/
    struct rubik{
        Face* faces[6];
        Historico* historico;
        int qtHistorico;
    };
#pragma endregion

/**************************************************************
* FUNÇÕES AUXILIARES
**************************************************************/
#pragma region AUXILIARES

    #include "helpers/constantes.cpp"
    #include "structures/historico.cpp"
    #include "helpers/criacao-destruicao.cpp"
    #include "helpers/operacoes-face.cpp"
    #include "helpers/cores.cpp"

    /**
     * Imprime uma determinada camada do cubo mágico
     * @param rubik: Objeto rubik a ser impresso
     * @param camada: Qual camada dele deverá ser impressa (1, 2, 3)
     */
    void imprimir_camada(Rubik* rubik, int camada){
        if(camada == 1){
            for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++){
                char linha[TAM_MAX_STRING_LINHA] = "\0";

                // Imprimindo os caracteres vazios
                for(short int j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, printf(" "));

                // Imprimindo a face superior
                printf(" ");
                face_obter_linha(rubik->faces[F_TOPO], i, linha);
                printf("%s\n", linha);
            }
            printf("\n");
        }
        else if(camada == 2){
            for(short int i = 0; i < 3; i++){
                char linha[TAM_MAX_STRING_LINHA];

                // Imprimindo a margem esquerda
                for(short int j = 0; j < MARGEM_ESQUERDA; j++, printf(" "));

                // Imprimindo a face lateral esquerda
                face_obter_linha(rubik->faces[F_ESQUERDA], i, linha);
                printf("%s", linha);
                printf(" ");

                // Imprimindo a face frontal
                face_obter_linha(rubik->faces[F_FRENTE], i, linha);
                printf("%s", linha);
                printf(" ");

                // Imprimindo a face lateral direita
                face_obter_linha(rubik->faces[F_DIREITA], i, linha);
                printf("%s", linha);
                printf(" ");

                // Imprimindo a face posterior
                face_obter_linha(rubik->faces[F_TRAS], i, linha);
                printf("%s\n", linha);
            }
            printf("\n");
        }
        else if(camada == 3){
            for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++){
                char linha[TAM_MAX_STRING_LINHA] = "\0";

                // Imprimindo os caracteres vazios
                for(short int j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, printf(" "));

                printf(" ");
                // Imprimindo a face inferior
                face_obter_linha(rubik->faces[F_BAIXO], i, linha);
                printf("%s\n", linha);
            }
            printf("\n");
        }
    }

    /**
    * Função para setar as cores de determinada face e camada
    * @param rubik: instância do cubo
    * @param face: face que contem a camada
    * @param camada: camada que sera alterada
    * @param cores: vetor contendo as novas cores
    */
    void set_camada(Rubik* rubik, short int face, const Camada* camada, const Cor* cores[3]){

        // Formula para descobrir o sentido da camada
        bool sentido = (camada->ci > camada->ti) || (camada->cj > camada->tj);

        short int count = 0;
        if(!sentido){
            // Sentido horário
            for (int x = camada->ci; x <= camada->ti; x++)
                for (int y = camada->cj; y <= camada->tj; y++)
                    rubik->faces[face]->adesivos[x][y]->cor = cores[count++];
        }
        else{
            // Sentido anti-horário
            for (int x = camada->ci; x >= camada->ti; x--)
                for (int y = camada->cj; y >= camada->tj; y--)
                    rubik->faces[face]->adesivos[x][y]->cor = cores[count++];
        }
    }

    /**
     * Verifica se um movimento é válido para determinado cubo,
     * já que um movimento realizado pelo cubo proibe que a mesma camada
     * seja movida novamente
     * @param rubik: Instância do cubo
     * @param mov: Movimento a ser verificado
     * @return bool
     */
    bool movimento_valido(Rubik* rubik, const Movimento* mov){
        return true;
    }

    /**
     * Função para definir a seed de aleatorização
     * @param seed
     */
    void set_srand(int seed){
        #ifndef SRAND
            srand(seed);
            #define SRAND
        #endif
    }

    /**
     * Retorna um movimento aleatório válido para um determinado
     * cubo mágico
     * @param rubik
     * @return const Movimento*
     */
    const Movimento* movimento_aleatorio(Rubik* rubik){
        uint8_t indiceMov = rand() % 18;
        const Movimento** mov = MOVIMENTOS[indiceMov];

        if(movimento_valido(rubik, *mov)) return *mov;
        else return *(MOVIMENTOS[(indiceMov+3) % 18]);
    }

#pragma endregion

/**************************************************************
* IMPLEMENTAÇÕES
**************************************************************/
#pragma region IMPLEMENTAÇÕES

    Rubik* rubik_criar(){
        Rubik* rubik = (Rubik*)malloc(sizeof(Rubik));

        const Cor* cores[6] = {
                &AZUL,
                &AMARELO,
                &VERMELHO,
                &BRANCO,
                &LARANJA,
                &VERDE
        };

        for(int i = 0; i < 6; i++)
            rubik->faces[i] = face_criar(cores[i]);

        Historico* h = historico_criar();
        rubik->historico = h;
        rubik->qtHistorico = atoi(getenv("QT_HISTORICO_MOVIMENTOS"));

        return rubik;
    }

    void rubik_destruir(Rubik** rubik){
        Rubik* r = *rubik;
        historico_destruir(&(r->historico));
        for(int i = 0; i < 6; i++)
            face_destruir(&(r->faces[i]));
        *rubik = NULL;
    }

    bool rubik_posicoes_iguais(char* pos1, char* pos2){
        if(strlen(pos1) != strlen(pos2)) return false;
        if(strlen(pos1) != 53) return false;

        for(short int i = 0; i < 53; i++){
            for(short int j = 0; j < 8; j++, i++){
                if(toupper(pos1[i]) != toupper(pos2[i])) return false;
            }
        }

        return true;
    }

    void rubik_imprimir(Rubik* rubik){
        /* #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif */

        imprimir_camada(rubik, 1);
        imprimir_camada(rubik, 2);
        imprimir_camada(rubik, 3);
    }

    void rubik_movimentar(Rubik* rubik, int num_args, ...){
        va_list list;
        va_start(list, num_args);

        for(int args = 0; args < num_args; args++){
            const Movimento* mov = va_arg(list, const Movimento*);

            for(uint8_t qt = 0; qt < mov->quantidade; qt++){

                const Cor* aux[3];
                for(uint8_t i = 0; i < 4; i++){
                    // Variáveis auxiliares
                    short int f = mov->faces[i];
                    const Camada* camada = mov->camadas[i];
                    const Cor* coresAtuais[3];

                    // Obter as cores da face e camada atual
                    extrair_cores(rubik, f, camada, coresAtuais);

                    // Setar as novas cores da camada atual
                    if(i > 0) set_camada(rubik, f, camada, aux);

                    // Ajustando os valores auxiliares
                    clonar_cores(coresAtuais, aux);
                }

                // Setando a primeira camada
                set_camada(rubik, mov->faces[0], mov->camadas[0], aux);

                // Girando a face fraca no sentido recebido
                face_girar(rubik->faces[mov->faceFraca] , mov->sentido);
            }

            // Adicionando movimento ao histórico
            historico_anexar(rubik, mov);
        }
    }

    bool rubik_definir_posicao(Rubik* rubik, const char* posicao){
        if(strlen(posicao) != 53) return false;
        const Cor* cores[6] = {
                &AZUL,
                &AMARELO,
                &VERMELHO,
                &BRANCO,
                &LARANJA,
                &VERDE
        };

        for(short int i = 0, count = 0; i < 6; i++){
            for(short int j = 0; j < 3; j++){
                for(short int k = 0; k < 3; k++){
                    if(j != 1 || k != 1){
                        const Cor* cor = NULL;
                        if(char_para_cor(posicao[count], &cor)) rubik->faces[i]->adesivos[j][k]->cor = cor;
                        else return false;
                        count++;
                    }
                    else rubik->faces[i]->adesivos[j][k]->cor = cores[i];
                }
            }
            count++;
        }

        return true;
    }

    bool rubik_redefinir(Rubik* rubik){
        rubik_definir_posicao(rubik, POS_RESOLVIDO);
        return true;
    }

    char* rubik_exportar(Rubik* rubik){
        char* str = (char*)calloc(sizeof(char), 54);
        short unsigned int count = 0;
        for(short int i = 0; i < 6; i++){
            for(short int j = 0; j < 3; j++)
                for(short int k = 0; k < 3; k++)
                    if(j != 1 || k != 1) str[count] = rubik->faces[i]->adesivos[j][k]->cor->cod, count++;
            if(i < 5) str[count] = '-', count++;
        }
        return str;
    }

    Rubik* rubik_importar(const char* pos){
        Rubik* rubik = rubik_criar();
        if(!rubik_definir_posicao(rubik, pos)) return NULL;
        return rubik;
    }

    char* rubik_embaralhar(Rubik* rubik, int qt){
        set_srand(time(NULL));

        char* str = (char*)calloc(sizeof(char), qt * 3 + 2);
        for(int i = 0; i < qt; i++){
            const Movimento* mov = movimento_aleatorio(rubik);
            strcat(str, mov->nome);
            strcat(str, " ");
            rubik_movimentar(rubik, 1, mov);
        }
        return str;
    }

    void rubik_imprimir_historico(Rubik* rubik){
        historico_imprimir(rubik->historico);
    }

#pragma endregion