#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <concepts>
#include <random>
#include <string>
#include <type_traits>

namespace snek {

    template<typename T>
    requires std::integral<T>
    T random_value(T min, T max) {
        static std::random_device rd{};
        static std::mt19937 rng(rd());
        return std::uniform_int_distribution<T>{min, max}(rng);
    }

    [[nodiscard]] float sgn(float value, float if_zero = 0);

    template<typename T>
    requires std::floating_point<T>
    [[nodiscard]] std::string to_string(T value) {
        const std::string str = std::to_string(value);
        return str.substr(0, str.find('.') + 2);
    }

    template<typename T>
    requires std::integral<T>
    [[nodiscard]] std::string to_string(T value) { return std::to_string(value); }

    template<typename T> concept VectorCoordinate = std::is_arithmetic_v<T> and requires(T t) { snek::to_string(t); };

    [[nodiscard]] std::string get_local_ip();
}

#endif // SNEK_IO_UTILITY_HPP
