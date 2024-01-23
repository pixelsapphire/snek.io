//
// Created by stas on 23.01.2024.
//

#include "player.hpp"

    const snek::vector_2f& snek::player::get_head() {
    return segments[0];
}

const std::vector<snek::vector_2f>& snek::player::get_segments() const {
    return segments;
}

void snek::player::update(float x_head, float y_head) {

    for (auto segment = segments.rbegin(); segment != segments.rend();) {
        segment->update((++segment)->get_x(), segment->get_y());
    }
    segments[0].update(x_head,y_head);
}

snek::player::player(float x, float y) {
    segments.push_back(snek::vector_2f(x,y));
}
