#include "player.hpp"
#include "utility.hpp"
#include <iostream>

snek::player::player(const snek::vector_2f& position) { segments.emplace_back(position); }

const snek::vector_2f& snek::player::get_head() { return segments[0]; }

const std::vector<snek::vector_2f>& snek::player::get_segments() const { return segments; }

void snek::player::update(const snek::vector_2f& head) {
    const snek::vector_2f tail = snek::vector_2f(segments.back());
    for (auto segment = segments.rbegin(); segment != segments.rend() - 1; ++segment) {
        *segment = *(segment + 1);
        std::cout<<"segment: x: "<<segment->get_x()<<" y: "<<segment->get_y()<<" changed to: x: "
        <<(segment + 1)->get_x()<<" y: "<<(segment + 1)->get_y()<<std::endl;
    }

    segments[0] = head;
    if (segments_queue > 0 && !is_nearby(tail, segments.back(), LEAST_SEGMENT_DISTANCE)) {//
        segments.emplace_back(tail);
        segments_queue--;
        std::cout<<"segment added: x: "<< tail.get_x()<<" y: "<< tail.get_y()<<std::endl;
    }
}

void snek::player::add_segments(uint8_t count) { segments_queue += count; }
