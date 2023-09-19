#include "rubik.h"
#include "utils/historico.c"
#include <time.h>

/**************************************************************
* VALORES CONSTANTES
**************************************************************/
#pragma region

    #define HORARIO 0
    #define ANTI_HORARIO 1

    #define F_FRENTE 0
    #define F_TOPO 1
    #define F_DIREITA 2
    #define F_BAIXO 3
    #define F_ESQUERDA 4
    #define F_TRAS 5

    #define QT_FACES 6
    #define QT_ADESIVOS_POR_LINHA 3
    #define QT_ADESIVOS_POR_FACE 9
    #define TAM_MAX_STRING_LINHA 100
    #define TAM_MAX_CARACTERES_VAZIOS 6
    #define MARGEM_ESQUERDA 3

#pragma endregion

/**************************************************************
* OBJETOS CONSTANTES
**************************************************************/
#pragma region

    const short int SEQUENCIA_X[4] = {0, 1, 5, 3};
    const short int SEQUENCIA_Y[4] = {0, 4, 5, 2};
    const short int SEQUENCIA_Z[4] = {1, 2, 3 ,4};

    const Cor AZUL     = {"Azul", 'B', "\x1b[38;2;1;126;255m"};
    const Cor AMARELO  = {"Amarelo", 'Y', "\x1b[38;2;245;255;0m"};
    const Cor VERMELHO = {"Vermelho", 'R', "\x1b[38;2;220;0;0m"};
    const Cor BRANCO   = {"Branco", 'W', "\033[1;37m"};
    const Cor LARANJA  = {"Laranja", 'O', "\x1b[38;2;255;138;25m"};
    const Cor VERDE    = {"Verde", 'G', "\033[38;2;0;225;1m"};

    const Camada CAMADA_U   = {0, 0, 0, 2};
    const Camada CAMADA_UA  = {0, 0, 2, 0};
    const Camada CAMADA_D   = {2, 2, 0, 2};
    const Camada CAMADA_DA  = {2, 2, 2, 0};
    const Camada CAMADA_R   = {0, 2, 2, 2};
    const Camada CAMADA_RA  = {2, 0, 2, 2};
    const Camada CAMADA_L   = {0, 2, 0, 0};
    const Camada CAMADA_LA  = {2, 0, 0, 0};
    const Camada CAMADA_M   = {0, 2, 1, 1};
    const Camada CAMADA_MA  = {2, 0, 1, 1};
    const Camada CAMADA_E   = {1, 1, 0, 2};
    const Camada CAMADA_EA  = {1, 1, 2, 0};

    #pragma region Movimento_F
        const Movimento MOV_F = {
                {F_TOPO, F_DIREITA, F_BAIXO, F_ESQUERDA},
                {&CAMADA_D, &CAMADA_L, &CAMADA_UA, &CAMADA_RA},
                F_FRENTE, HORARIO, 1, 0, "F"
        };
        const Movimento* F = &MOV_F;

        const Movimento MOV_FA = {
                {F_TOPO, F_ESQUERDA, F_BAIXO, F_DIREITA},
                {&CAMADA_DA, &CAMADA_R, &CAMADA_U, &CAMADA_LA},
                F_FRENTE, ANTI_HORARIO, 1, 1, "F'"
        };
        const Movimento* FA = &MOV_FA;

        const Movimento MOV_F2 = {
                {F_TOPO, F_DIREITA, F_BAIXO, F_ESQUERDA},
                {&CAMADA_D, &CAMADA_L, &CAMADA_UA, &CAMADA_RA},
                F_FRENTE, HORARIO, 2, 2, "F2"
        };
        const Movimento* F2 = &MOV_F2;
    #pragma endregion

    #pragma region MOVIMENTO_U
        const Movimento MOV_U = {
            {F_FRENTE, F_ESQUERDA, F_TRAS, F_DIREITA},
            {&CAMADA_U, &CAMADA_U, &CAMADA_U, &CAMADA_U},
            F_TOPO, HORARIO, 1, 3, "U"
        };
        const Movimento* U = &MOV_U;

        const Movimento MOV_UA = {
                {F_FRENTE, F_DIREITA, F_TRAS, F_ESQUERDA},
                {&CAMADA_UA, &CAMADA_UA, &CAMADA_UA, &CAMADA_UA},
                F_TOPO, ANTI_HORARIO, 1, 4, "U'"
        };
        const Movimento* UA = &MOV_UA;

        const Movimento MOV_U2 = {
                {F_FRENTE, F_ESQUERDA, F_TRAS, F_DIREITA},
                {&CAMADA_U, &CAMADA_U, &CAMADA_U, &CAMADA_U},
                F_TOPO, HORARIO, 2, 5, "U2"
        };
        const Movimento* U2 = &MOV_U2;
    #pragma endregion

    #pragma region Movimento_R
        const Movimento MOV_R = {
                {F_FRENTE, F_TOPO, F_TRAS, F_BAIXO},
                {&CAMADA_RA, &CAMADA_RA, &CAMADA_L, &CAMADA_RA},
                F_DIREITA, HORARIO, 1, 6, "R"
        };
        const Movimento* R = &MOV_R;

        const Movimento MOV_RA = {
                {F_FRENTE, F_BAIXO, F_TRAS, F_TOPO},
                {&CAMADA_R, &CAMADA_R, &CAMADA_LA, &CAMADA_R},
                F_DIREITA, ANTI_HORARIO, 1, 7, "R'"
        };
        const Movimento* RA = &MOV_RA;

        const Movimento MOV_R2 = {
                {F_FRENTE, F_TOPO, F_TRAS, F_BAIXO},
                {&CAMADA_RA, &CAMADA_RA, &CAMADA_L, &CAMADA_RA},
                F_DIREITA, HORARIO, 2, 8, "R2"
        };
        const Movimento* R2 = &MOV_R2;
    #pragma endregion

    #pragma region MOVIMENTO_D
        const Movimento MOV_D = {
                {F_FRENTE, F_DIREITA, F_TRAS, F_ESQUERDA},
                {&CAMADA_D, &CAMADA_D, &CAMADA_D, &CAMADA_D},
                F_BAIXO, HORARIO, 1, 9, "D"
        };
        const Movimento* D = &MOV_D;

        const Movimento MOV_DA = {
                {F_FRENTE, F_ESQUERDA, F_TRAS, F_DIREITA},
                {&CAMADA_DA, &CAMADA_DA, &CAMADA_DA, &CAMADA_DA},
                F_BAIXO, ANTI_HORARIO, 1, 10, "D'"
        };
        const Movimento* DA = &MOV_DA;

        const Movimento MOV_D2 = {
                {F_FRENTE, F_DIREITA, F_TRAS, F_ESQUERDA},
                {&CAMADA_D, &CAMADA_D, &CAMADA_D, &CAMADA_D},
                F_BAIXO, HORARIO, 2, 11, "D2"
        };
        const Movimento* D2 = &MOV_D2;
    #pragma endregion

    #pragma region Movimento_L
        const Movimento MOV_L = {
                {F_FRENTE, F_BAIXO, F_TRAS, F_TOPO},
                {&CAMADA_L, &CAMADA_L, &CAMADA_RA, &CAMADA_L},
                F_ESQUERDA, HORARIO, 1, 12, "L"
        };
        const Movimento* L = &MOV_L;

        const Movimento MOV_LA = {
                {F_FRENTE, F_TOPO, F_TRAS, F_BAIXO},
                {&CAMADA_LA, &CAMADA_LA, &CAMADA_R, &CAMADA_LA},
                F_ESQUERDA, ANTI_HORARIO, 1, 13, "L'"
        };
        const Movimento* LA = &MOV_LA;

        const Movimento MOV_L2 = {
                {F_FRENTE, F_BAIXO, F_TRAS, F_TOPO},
                {&CAMADA_L, &CAMADA_L, &CAMADA_RA, &CAMADA_L},
                F_ESQUERDA, HORARIO, 2, 14, "L2"
        };
        const Movimento* L2 = &MOV_L2;
    #pragma endregion

    #pragma region Movimento_B
        const Movimento MOV_B = {
                {F_TOPO, F_ESQUERDA, F_BAIXO, F_DIREITA},
                {&CAMADA_UA, &CAMADA_L, &CAMADA_D, &CAMADA_RA},
                F_TRAS, HORARIO, 1, 15, "B"
        };
        const Movimento* B = &MOV_B;

        const Movimento MOV_BA = {
                {F_TOPO, F_DIREITA, F_BAIXO, F_ESQUERDA},
                {&CAMADA_U, &CAMADA_R, &CAMADA_DA, &CAMADA_LA},
                F_TRAS, ANTI_HORARIO, 1, 16, "B'"
        };
        const Movimento* BA = &MOV_BA;

        const Movimento MOV_B2 = {
                {F_TOPO, F_ESQUERDA, F_BAIXO, F_DIREITA},
                {&CAMADA_UA, &CAMADA_L, &CAMADA_D, &CAMADA_RA},
                F_TRAS, HORARIO, 2, 17, "B2"
        };
        const Movimento* B2 = &MOV_B2;
    #pragma endregion

    const Movimento** MOVIMENTOS[18] = {
            &F, &FA, &F2,
            &U, &UA, &U2,
            &R, &RA, &R2,
            &D, &DA, &D2,
            &L, &LA, &L2,
            &B, &BA, &B2
    };

#pragma endregion

/**************************************************************
* FUNÇÕES AUXILIARES
**************************************************************/
#pragma region AUXILIARES

    /**
     * Função auxiliar para alocar um adesivo
     * @param cor: Cor que o adesivo receberá
     * @return Adesivo*: Endereço do ponteiro criado
     */
    Adesivo* adesivo_criar(const Cor* cor){
        Adesivo* adesivo = (Adesivo*)malloc(sizeof(Adesivo));
        adesivo->cor = cor;
        return adesivo;
    }

    /**
    * Função auxiliar para desalocar um adesivo
    * @Adesivo** adesivo: Endereço do ponteiro de um adesivo
    */
    void adesivo_destruir(Adesivo** adesivo){
        free(*adesivo);
        *adesivo = NULL;
    }

    /**
     * Função auxiliar para alocar uma face
     * @param cor: Cor que a face devera inicializar
     * @return Face*: Endereço da face criada
     */
    Face* face_criar(const Cor* cor){
        Face* face = (Face*)malloc(sizeof(Face));

        for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++){
            for(short int j = 0; j < QT_ADESIVOS_POR_LINHA; j++){
                Adesivo* adesivo = adesivo_criar(cor);
                face->adesivos[i][j] = adesivo;
            }
        }

        return face;
    }

    /**
    * Função auxiliar para alocar uma face
    * @param Face** face: Endereço do ponteiro da face
    */
    void face_destruir(Face** face){
        Face* f = *face;
        for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++)
            for(short int j = 0; j < QT_ADESIVOS_POR_LINHA; j++)
                adesivo_destruir(&(f->adesivos[i][j]));
        *face = NULL;
    }


    void face_imprimir(Face* face){
        for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++){
            for(short int j = 0; j < QT_ADESIVOS_POR_LINHA; j++){
                printf("%s, ", face->adesivos[i][j]->cor->nome);
            }
        }
        printf("\b\b\n");
    }

    /**
     * Copia todas as cores de uma face para outra, sempre da
     * origem para o destino
     * @param Face* origem: De onde virão os novos valores
     * @param Face* destino: Onde os novos valores devem ser copiados
     */
    void face_copiar(const Face* origem, Face* destino){
        for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++)
            for(short int j = 0; j < QT_ADESIVOS_POR_LINHA; j++)
                destino->adesivos[i][j] = origem->adesivos[i][j];
    }

    /**
     * Transpõe uma matriz 3x3 de adesivos (Face). Ou seja,
     * transforma as colunas em linhas, e vice-versa
     * @param face
     */
    void face_transpor(Face* face){
        for(uint8_t i = 0; i < 3; i++){
            for(uint8_t j = i + 1; j < 3; j++){
                Adesivo* temp = face->adesivos[i][j];
                face->adesivos[i][j] = face->adesivos[j][i];
                face->adesivos[j][i] = temp;
            }
        }
    }

    /**
     * Troca duas linhas de uma determinada face
     * @param face: face alvo
     * @param lin1: número da primeira coluna
     * @param lin2: número da segunda coluna
     */
    void face_trocar_linhas(Face* face, uint8_t lin1, uint8_t lin2){
        for(uint8_t i = 0; i < 3; i++){
            Adesivo* temp = face->adesivos[lin1][i];
            face->adesivos[lin1][i] = face->adesivos[lin2][i];
            face->adesivos[lin2][i] = temp;
        }
    }

    /**
     * Troca duas colunas de uma determinada face
     * @param face: face alvo
     * @param col1: número da primeira coluna
     * @param col2: número da segunda coluna
     */
    void face_trocar_colunas(Face* face, uint8_t col1, uint8_t col2){
        for(uint8_t i = 0; i < 3; i++){
            Adesivo* temp = face->adesivos[i][col1];
            face->adesivos[i][col1] = face->adesivos[i][col2];
            face->adesivos[i][col2] = temp;
        }
    }

    /**
    * Função responsável por girar uma determinada face do cubo
    * @param face: face a ser girada
    * @param sentido: sentido do movimento (0) horário, (1) anti-horário
    */
    bool face_girar(Face* face, short int sentido){
        if(sentido != 0  && sentido != 1) return false;

        face_transpor(face);
        if(sentido) face_trocar_linhas(face, 0, 2);
        else face_trocar_colunas(face, 0, 2);

        return true;
    }


    /**
     * Obtém uma string de uma determinada linha
     * de uma face para impressão
     * @param face: Ponteiro da face que a string será extraida
     * @param linha: Qual linha da face deve ser extraida
     * @param str: Retorno da linha em formato de string
     */
    void obter_linha_face(Face* face, const short int linha, char* str){
        str[0] = '\0';
        for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++){
            strcat(str, face->adesivos[linha][i]->cor->ch);
            strcat(str, CHAR_QUAD);
            strcat(str, REDEFINIR_COR);
        }
    }

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
                obter_linha_face(rubik->faces[F_TOPO], i, linha);
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
                obter_linha_face(rubik->faces[F_ESQUERDA], i, linha);
                printf("%s", linha);
                printf(" ");

                // Imprimindo a face frontal
                obter_linha_face(rubik->faces[F_FRENTE], i, linha);
                printf("%s", linha);
                printf(" ");

                // Imprimindo a face lateral direita
                obter_linha_face(rubik->faces[F_DIREITA], i, linha);
                printf("%s", linha);
                printf(" ");

                // Imprimindo a face posterior
                obter_linha_face(rubik->faces[F_TRAS], i, linha);
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
                obter_linha_face(rubik->faces[F_BAIXO], i, linha);
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
    * Extrai as cores de uma determinada face e camada de uma instância do cubo,
    * valores serão armazenados nas 'cores'
    * @param rubik: instancia do cubo a ser extraido
    * @param face: face que contém as camadas a serem extraidas
    * @param camada: qual camada da face deve ser copiada
    * @param cores: array para qual as cores serão copiadas
    * @param sentido: sentido do movimento, 0 horário, 1 anti-horário
    */
    void extrair_cores(Rubik* rubik, short int face, const Camada* camada, const Cor* cores[3]){

        // Formula para descobrir o sentido da camada
        bool sentido = (camada->ci > camada->ti) || (camada->cj > camada->tj);

        short int count = 0;
        if(!sentido){
            // Sentido horário
            for (int x = camada->ci; x <= camada->ti; x++)
                for (int y = camada->cj; y <= camada->tj; y++)
                    cores[count++] = rubik->faces[face]->adesivos[x][y]->cor;
        }
        else{
            // Sentido anti-horário
            for (int x = camada->ci; x >= camada->ti; x--)
                for (int y = camada->cj; y >= camada->tj; y--)
                    cores[count++] = rubik->faces[face]->adesivos[x][y]->cor;
        }
    }

    /**
    * Função para clonar um array de cores para outro
    * @param origem: de onde as cores devem ser copiadas
    * @param destino: para onde elas serão copiadas
    * @return bool: retorna true para sucesso, false para erro
    */
    bool clonar_cores(const Cor* origem[3], const Cor* destino[3]){
        if(origem == NULL || destino == NULL) return false;
        for(int i = 0; i < 3; i++)
            destino[i] = origem[i];
        return true;
    }

    /**
    * Converte um determinado caracter para sua respectiva cor
    * @param ch: caracter a ser convertido
    * @param cor: ponteiro para a cor depois de convertida
    * @return bool: true para sucesso, e false para erro
    */
    bool char_para_cor(char ch, const Cor** cor){
        switch(toupper(ch)){
            case 'B': *cor = &AZUL;
                break;
            case 'Y': *cor = &AMARELO;
                break;
            case 'R': *cor = &VERMELHO;
                break;
            case 'W': *cor = &BRANCO;
                break;
            case 'O': *cor = &LARANJA;
                break;
            case 'G': *cor = &VERDE;
                break;
            default: return false;
        }
        return true;
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

    bool rubik_definir_posicao(Rubik* rubik, char* posicao){
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

    Rubik* rubik_importar(char* pos){
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