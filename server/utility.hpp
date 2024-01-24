
#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <random>
#include <cmath>
#include "vector_2f.hpp"

namespace snek {

    template<typename T>
    requires std::integral<T>
    T random_value(T min, T max) {
        static std::random_device rd{};
        static std::mt19937 rng(rd());
        static std::uniform_int_distribution<T> dist{min, max};
        return dist(rng);
    }

    bool is_nearby (const snek::vector_2f& position, const snek::vector_2f& segment, float r);
}

#endif //SNEK_IO_UTILITY_HPP
