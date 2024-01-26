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

std::string snek::vector_2f::str() const { return std::to_string(x) + "x" + std::to_string(y) + "y"; }


bool snek::vector_2f::operator==(const snek::vector_2f& other) const { return x == other.x and y == other.y; }