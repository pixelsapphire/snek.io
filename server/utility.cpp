#include "utility.hpp"

bool snek::is_nearby(const snek::vector_2f &position, const snek::vector_2f &segment, float distance) {
    float length = powf(position.get_x() - segment.get_x(), 2) +
                   powf(position.get_y() - segment.get_y(), 2);
    return length <= powf(distance, 2);
}
