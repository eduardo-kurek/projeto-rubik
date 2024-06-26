#pragma once

#include <random>

namespace svc {

    class Random {

        public:
            static std::mt19937_64 MT;
            static int Int(int min, int max);
            static float Float(float min, float max);

    };

}