#include <random>

namespace svc {

    class Random {

        public:
            static std::mt19937_64 MT;
            static int uniform_int_distribution(int min, int max);

    };

}