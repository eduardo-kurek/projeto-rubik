#pragma once

#include "Move.h"
#include <functional>

namespace Restriction{

    // Função que obtém os movimentos suplementares de um outro movimento
    std::vector<const Move*> SUPPLEMENTATION(const Move* move, const Move* lastMove);

    /**
     * Função que obtém os movimentos suplementares de um outro movimento, e também os complementares
     * caso o lastMove sejá seu complementar
     */
    std::vector<const Move*> SUPPLEMENTATION_ORACLE(const Move* move, const Move* lastMove);

    // Função que obtém os movimentos complementares de um outro movimento
    std::vector<const Move*> COMPLEMENTATION(const Move* move, const Move* lastMove);

    // Função que obtém os movimentos complementares e suplementares de um outro movimento
    std::vector<const Move*> BOTH(const Move* move, const Move* lastMove);

    // Função que não obtém nenhum movimento
    std::vector<const Move*> NOTHING(const Move*, const Move*);

}