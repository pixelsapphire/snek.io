#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <string>
#include <random>
#include "vector2f.hpp"

namespace snek {

    template<typename T>
    requires std::integral<T>
    T random_value(T min, T max) {
        static std::random_device rd{};
        static std::mt19937 rng(rd());
        return std::uniform_int_distribution<T>{min, max}(rng);
    }

    [[nodiscard]] float sgn(float value, float if_zero = 0);

    [[nodiscard]] bool is_nearby(const snek::vector2f& position, const snek::vector2f& segment, float distance);

    [[nodiscard]] std::string get_local_ip();
}

#endif // SNEK_IO_UTILITY_HPP
