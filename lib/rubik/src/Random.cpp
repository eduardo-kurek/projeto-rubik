#include "Random.h"

namespace svc {

    std::mt19937_64 Random::MT(std::random_device{}());

    int Random::Int(int min, int max){
        std::uniform_int_distribution<int> dist(min, max);
        return dist(MT);
    }

    float Random::Float(float min, float max){
        std::uniform_real_distribution<float> dist(min, max);
        return dist(MT);
    }

}