#include "../rubik.h"

/**************************************************************
* AUXILIARES
**************************************************************/

No* historico_no_criar(No* sentinela, const Movimento* elemento){
    No* no = (No*)malloc(sizeof(No));
    no->prox = sentinela;
    no->ant = sentinela;
    no->dado = elemento;
    return no;
}

No* historico_no_endereco(Historico* h, int posicao){
    No* aux = h->sentinela;
    for(int i = 0; i < posicao; i++) aux = aux->prox;
    return aux;
}

/**************************************************************
* IMPLEMENTAÇÕES
**************************************************************/

Historico* historico_criar(){
    Historico *h = (Historico*)malloc(sizeof(Historico));
    No* sentinela = (No*)malloc(sizeof(No));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;

    h->sentinela = sentinela;
    h->qtde = 0;
    return h;
}

void historico_destruir(Historico** endHistorico){
    Historico* l = *endHistorico;

    No* aux = l->sentinela->ant;
    for(int i = 0; i < l->qtde; i++){
        No* prox = aux->ant;
        free(aux);
        aux = prox;
    }

    free(*endHistorico);
    endHistorico = NULL;
}

bool historico_remover_posicao(Historico* h, int posicao){
    if(posicao < 0 || posicao >= h->qtde) return false;

    No* esquerda = historico_no_endereco(h, posicao);
    No* direita = esquerda->prox->prox;

    // Removendo o nó da direita
    free(esquerda->prox);
    esquerda->prox = direita;
    direita->ant = esquerda;
    h->qtde--;

    return true;
}

bool historico_anexar(Rubik* rubik, const Movimento* elemento){
    Historico* h = rubik->historico;
    No* novo = historico_no_criar(h->sentinela, elemento);

    if(h->qtde == rubik->qtHistorico)
        historico_remover_posicao(h, 0);

    novo->ant = h->sentinela->ant;
    h->sentinela->ant->prox = novo;
    h->sentinela->ant = novo;
    h->qtde++;
    return true;
}

void historico_imprimir(Historico* h){
    No* aux = h->sentinela->prox;
    for(int i = 0; i < h->qtde; i++){
        printf("%s ", aux->dado->nome);
        aux = aux->prox;
    }
    printf("\b\b\n");
}