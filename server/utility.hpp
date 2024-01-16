
#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <random>

namespace snek{

    template<typename T>
    requires std::integral<T>
    T random_value(T min, T max) {
        static std::mt19937 rng(std::random_device{}());
        return std::uniform_int_distribution<T>(min, max)(rng);
    }
}

#endif //SNEK_IO_UTILITY_HPP
