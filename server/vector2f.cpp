#include <algorithm>
#include <cmath>
#include "common_utility.hpp"
#include "vector2f.hpp"

snek::vector2f::vector2f() : x(0), y(0) {}

snek::vector2f::vector2f(float x, float y) {
    this->x = x;
    this->y = y;
}

snek::vector2f snek::vector2f::operator+(const snek::vector2f& other) const { return {x + other.x, y + other.y}; }

snek::vector2f& snek::vector2f::operator+=(const snek::vector2f& other) { return *this = *this + other; }

snek::vector2f snek::vector2f::operator-(const snek::vector2f& other) const { return {x - other.x, y - other.y}; }

snek::vector2f& snek::vector2f::operator-=(const snek::vector2f& other) { return *this = *this - other; }

snek::vector2f snek::vector2f::operator*(float scalar) const { return {x * scalar, y * scalar}; }

snek::vector2f snek::operator*(float scalar, const snek::vector2f& vector) { return vector * scalar; }

snek::vector2f& snek::vector2f::operator*=(float scalar) { return *this = *this * scalar; }

snek::vector2f snek::vector2f::operator/(float scalar) const { return {x / scalar, y / scalar}; }

snek::vector2f& snek::vector2f::operator/=(float scalar) { return *this = *this / scalar; }

bool snek::vector2f::operator==(const snek::vector2f& other) const { return x == other.x and y == other.y; }

float snek::vector2f::length() const { return __clang_std::sqrtf(x * x + y * y); }

snek::vector2f snek::vector2f::normalized() const {
    const float len = length();
    if (len == 0) return {0, 0};
    return {x / len, y / len};
}

std::string snek::vector2f::str() const { return std::to_string(x) + "x" + std::to_string(y) + "y"; }

snek::vector2f snek::vector2f::direction_change(const snek::vector2f& origin, const snek::vector2f& target,
                                                float delta_max) {
    float delta = __clang_std::atan2f(target.y, target.x) -
                  __clang_std::atan2f(origin.y, origin.x);
    if (delta > M_PI) delta -= 2 * M_PI;
    else if (delta < -M_PI) delta += 2 * M_PI;
    delta = std::clamp(delta, -delta_max, delta_max);
    return {origin.x * __clang_std::cosf(delta) - origin.y * __clang_std::sinf(delta),
            origin.x * __clang_std::sinf(delta) + origin.y * __clang_std::cosf(delta)};
}

const snek::vector2f snek::vector2f::zero = {0, 0};