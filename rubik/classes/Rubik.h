#pragma once

#include "auxiliares/Face.h"
#include "auxiliares/constantes.h"
#include "auxiliares/Move.h"
#include "auxiliares/Restriction.h"
#include <functional>
#include <cstdarg>
#include <string>
#include <list>

class Rubik{

    struct MoveStatus{
        const Move* move;
        bool isValid;
    };

    using RestrictionFunction = std::function<std::vector<const Move*>(const Move*)>;

    Face faces[6];
    std::list<const Move*> historic;
    std::vector<bool> validMoves;
    std::vector<const Move*> restrictedMoves;
    RestrictionFunction restrictionFunction = Restriction::SUPPLEMENTATION;

    /**
     * Aplica a restrição ao cubo mágico de acordo com o retorno da função
     * this->restrictionFunction
     * @param lastMove
     */
    void restrict(const Move* lastMove);

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
     * Imprime o cubo mágico
     * @param clear: limpar o terminal antes da impressão?
     */
    void print(bool clear = false) const;

    /**
     * Imprime o histórico dos últimos 20 movimentos do cubo
     */
    void printHistoric() const;

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

};