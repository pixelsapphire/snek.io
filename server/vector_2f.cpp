#include <algorithm>
#include <cmath>
#include "common_utility.hpp"
#include "vector_2f.hpp"

snek::vector_2f::vector_2f() : x(0), y(0) {}

snek::vector_2f::vector_2f(float x, float y) {
    this->x = x;
    this->y = y;
}

snek::vector_2f::vector_2f(int x, int y) {
    this->x = float(x);
    this->y = float(y);
}

float snek::vector_2f::get_x() const { return x; }

float snek::vector_2f::get_y() const { return y; }

snek::vector_2f snek::vector_2f::operator+(const snek::vector_2f& other) const { return {x + other.x, y + other.y}; }

snek::vector_2f& snek::vector_2f::operator+=(const snek::vector_2f& other) { return *this = *this + other; }

snek::vector_2f snek::vector_2f::operator-(const snek::vector_2f& other) const { return {x - other.x, y - other.y}; }

snek::vector_2f& snek::vector_2f::operator-=(const snek::vector_2f& other) { return *this = *this - other; }

snek::vector_2f snek::vector_2f::operator*(float scalar) const { return {x * scalar, y * scalar}; }

snek::vector_2f snek::operator*(float scalar, const snek::vector_2f& vector) { return vector * scalar; }

snek::vector_2f& snek::vector_2f::operator*=(float scalar) { return *this = *this * scalar; }

snek::vector_2f snek::vector_2f::operator/(float scalar) const { return {x / scalar, y / scalar}; }

snek::vector_2f& snek::vector_2f::operator/=(float scalar) { return *this = *this / scalar; }

bool snek::vector_2f::operator==(const snek::vector_2f& other) const { return x == other.x and y == other.y; }

float snek::vector_2f::length() const { return __clang_std::sqrtf(x * x + y * y); }

snek::vector_2f snek::vector_2f::normalized() const {
    const float len = length();
    return {x / len, y / len};
}

std::string snek::vector_2f::str() const { return std::to_string(x) + "x" + std::to_string(y) + "y"; }

snek::vector_2f snek::vector_2f::direction_change(const snek::vector_2f& origin, const snek::vector_2f& target,
                                                  float delta_max) {
    float delta = __clang_std::atan2f(target.get_y(), target.get_x()) -
                  __clang_std::atan2f(origin.get_y(), origin.get_x());
    if (delta > M_PI) delta -= 2 * M_PI;
    else if (delta < -M_PI) delta += 2 * M_PI;
//    delta = __clang_std::fmodf(delta, 2 * M_PI);
    delta = std::clamp(delta, -delta_max, delta_max);
    return {origin.get_x() * __clang_std::cosf(delta) - origin.get_y() * __clang_std::sinf(delta),
            origin.get_x() * __clang_std::sinf(delta) + origin.get_y() * __clang_std::cosf(delta)};
}

const snek::vector_2f snek::vector_2f::zero = {0, 0};