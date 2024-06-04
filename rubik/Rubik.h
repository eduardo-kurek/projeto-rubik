#pragma once

#include "auxiliares/Face.h"
#include "auxiliares/constantes.h"
#include "auxiliares/Move.h"
#include "auxiliares/Restriction.h"
#include <functional>
#include <cstdarg>
#include <string>
#include <queue>
#include <vector>

class Rubik{

    using RestrictionFunction = std::function<std::vector<const Move*>(const Move*, const Move*)>;

    Face faces[6];
    const Move* lastMove = nullptr;
    std::queue<const Move*> historic;
    std::vector<const Move*> restrictedMoves;
    RestrictionFunction restrictionFunction = Restriction::SUPPLEMENTATION_ORACLE;

    /**
     * Aplica a restrição ao cubo mágico de acordo com o retorno da função
     * this->restrictionFunction
     * @param move
     * @param lastMove
     */
    void restrict(const Move* move, const Move* lastMove);

    /**
     * Conta quantos adesivos esão iguais em relação a outra
     * peça de outro cubo mágico
     * @param other: outra instância a ser comparada
     * @param corner: corner a ser comparada
     * @param offset: caso necessário comparar com o adesivo da "frente"
     * @return
     */
    //uint8_t countEqualStickers(const Rubik& other, const Corner& corner, const uint8_t offset = 0) const;


public:
    bool forceRestrictedMoves = false;

    /**
     * Construtor padrão da classe, inicia o cubo já resolvido
     */
    Rubik();

    /**
     * Construtor para iniciar o cubo com uma posição específica
     * @param position: string contendo a posição a ser iniciada
     */
    explicit Rubik(const std::string& position);

    /**
     * Getter das faces
     * @return
     */
    const Face* getFaces() const;

    /**
     * Define a função de restrição usada para calcular o vetor
     * de movimentos restritos do cubo.
     * @param restrictionFunction: Funções encontradas no arquivo
     * "auxiliares/Restriction"
     */
    void setRestrictionFunction(const RestrictionFunction& restrictionFunction);

    /**
     * Limpa o vetor de movimentos restritos do cubo
     */
    void clearRestrictedMoves();

    /**
     * Limpa o histórico de movimentos
     */
    void clearHistoric();

    /**
     * Imprime o cubo mágico
     * @param clear: limpar o terminal antes da impressão?
     */
    void print(bool clear = false) const;

    /**
     * Imprime o histórico dos últimos 20 movimentos do cubo
     */
    void printHistoric() const;

    /**
     * Obtém o histórico de movimentos do cubo
     * @return
     */
    std::vector<const Move*> getHistoric() const;

    /**
     * Obtém o histórico de movimentos do cubo em string
     * @return
     */
    std::string getHistoricString() const;

    /**
     * Imprime a lista com os movimentos restritos
     */
    void printRestrictedMoves() const;

    /**
     * Reseta o cubo mágico para a posição resolvida
     */
    void reset();

    /**
     * Extrai o cubo mágico para uma string do seguinte formato:
     * "BBBBBBBB-YYYYYYYY-RRRRRRRR-WWWWWWWW-OOOOOOOO-GGGGGGGG"
     *      ^        ^        ^        ^        ^        ^
     *   Frente    Topo    Direita  Baixo   Esquerda    Trás
     * @return
     */
    std::string extract() const;

    /**
     * Defini uma posição do cubo mágico de acordo com uma string
     * da posição
     * @param position
     */
    void setPosition(const std::string& position);

    /**
     * Realiza o movimento do cubo mágico e adiciona ao histórico
     * @param numArgs
     * @param ...
     */
    void move(int numArgs, ...);

    /**
     * Realiza o movimento do cubo mágico e adiciona ao histórico
     * @param std::vector<const Move*> vetor contendo os movimentos
     */
    void move(std::vector<const Move*> moves);

    /**
     * Retorna um array com todos os movimentos válidos na instância atual do cubo
     * @return
     */
    std::vector<const Move*> getValidMoves();

    /**
     * Embaralha o cubo mágico
     * @param quantity: quantidade de movimentos no embaralhamento
     */
    void scramble(int quantity = 20);

    /**
     * Sobrecarga de operador para impressão do cubo
     * @param os
     * @param rubik
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const Rubik* rubik);

    /**
     * Comparação de 2 cubos
     */
    bool operator==(const Rubik& other) const;

};