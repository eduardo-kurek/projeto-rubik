#pragma once

#include "Move.h"
#include <functional>

namespace Restriction{

    // Função que obtém os movimentos suplementares de um outro movimento
    std::vector<const Move*> SUPPLEMENTATION(const Move* move);

    // Função que obtém os movimentos complementares de um outro movimento
    std::vector<const Move*> COMPLEMENTATION(const Move* move);

    // Função que obtém os movimentos complementares e suplementares de um outro movimento
    std::vector<const Move*> BOTH(const Move* move);

    // Função que não obtém nenhum movimento
    std::vector<const Move*> NOTHING(const Move*);

}