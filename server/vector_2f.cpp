#include "vector_2f.hpp"


snek::vector_2f::vector_2f(float x, float y) {
    this->x = x;
    this->y = y;
}

float snek::vector_2f::get_x() const {
    return x;
}

float snek::vector_2f::get_y() const {
    return y;
}

void snek::vector_2f::update(float x_value, float y_value) {
    x = x_value;
    y = y_value;
}


snek::vector_2f::vector_2f(int x, int y) {
    this->x = float(x);
    this->y = float(y);
}
