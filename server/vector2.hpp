#ifndef SNEK_IO_VECTOR2_HPP
#define SNEK_IO_VECTOR2_HPP

#include <algorithm>
#include <cmath>
#include <string>
#include <type_traits>
#include "common_utility.hpp"
#include "utility.hpp"

namespace snek {

    template<snek::VectorCoordinate T>
    struct vector2 {

        T x, y;

        static const vector2<T> zero;

        vector2() : x(0), y(0) {}

        vector2(T x, T y) : x(x), y(y) {}

        vector2& operator=(const vector2& other) = default;

        vector2& operator=(vector2&& other) noexcept = default;

        vector2(const vector2& other) = default;

        vector2(vector2&& other) noexcept = default;

        vector2 operator+(const vector2& other) const { return {x + other.x, y + other.y}; }

        vector2& operator+=(const vector2& other) { return *this = *this + other; }

        vector2 operator-(const vector2& other) const { return {x - other.x, y - other.y}; }

        vector2& operator-=(const vector2& other) { return *this = *this - other; }

        vector2 operator-() const { return {-x, -y}; }

        template<typename S>
        requires std::is_arithmetic_v<S>
        vector2 operator*(S scalar) const { return {x * scalar, y * scalar}; }

        template<typename S>
        requires std::is_arithmetic_v<S>
        vector2& operator*=(S scalar) { return *this = *this * scalar; }

        template<typename S>
        requires std::is_arithmetic_v<S>
        vector2 operator/(S scalar) const { return {x / scalar, y / scalar}; }

        template<typename S>
        requires std::is_arithmetic_v<S>
        vector2& operator/=(S scalar) { return *this = *this / scalar; }

        bool operator==(const vector2& other) const { return x == other.x and y == other.y; };

        template<snek::VectorCoordinate U>
        requires std::is_convertible_v<T, U>
        snek::vector2<U> cast() const { return {U(x), U(y)}; }

        [[nodiscard]] float length() const { return __clang_std::sqrtf(x * x + y * y); }

        [[nodiscard]] vector2 normalized() const {
            const float l = length();
            return l == 0 ? snek::vector2<T>::zero : snek::vector2(x / l, y / l);
        }

        [[nodiscard]] std::string str() const { return snek::to_string(x) + "x" + snek::to_string(y) + "y"; };

        [[nodiscard]] static T distance(const vector2& a, const vector2& b) {
            return __clang_std::sqrtf(__clang_std::powf(a.x - b.x, 2) + __clang_std::powf(a.y - b.y, 2));
        }

        template<typename S>
        requires std::is_arithmetic_v<S>
        [[nodiscard]] static snek::vector2<T> direction_change(const snek::vector2<T>& origin,
                                                               const snek::vector2<T>& target,
                                                               S delta_max) {
            float delta = __clang_std::atan2f(target.y, target.x) - __clang_std::atan2f(origin.y, origin.x);
            if (delta > M_PI) delta -= 2 * M_PI;
            else if (delta < -M_PI) delta += 2 * M_PI;
            delta = std::clamp(delta, -delta_max, delta_max);
            return {origin.x * __clang_std::cosf(delta) - origin.y * __clang_std::sinf(delta),
                    origin.x * __clang_std::sinf(delta) + origin.y * __clang_std::cosf(delta)};
        }
    };

    typedef vector2<float> vector2f;
    typedef vector2<int> vector2i;
}

template<snek::VectorCoordinate T, typename S>
snek::vector2<T> operator*(S scalar, const snek::vector2<T>& vector) { return vector * scalar; }

template<snek::VectorCoordinate T>
const snek::vector2<T> snek::vector2<T>::zero = snek::vector2<T>(T(0), T(0));

#endif //SNEK_IO_VECTOR2_HPP
