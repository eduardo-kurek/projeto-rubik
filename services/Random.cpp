#include "Random.h"

namespace svc {

    std::mt19937_64 Random::MT(37u);

    int Random::uniform_int_distribution(int min, int max){
        std::uniform_int_distribution<int> dist(min, max);
        return dist(MT);
    }

}