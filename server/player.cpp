#include "player.hpp"

snek::player::player(const snek::vector_2f& position) { segments.emplace_back(position); }

const snek::vector_2f& snek::player::get_head() { return segments[0]; }

const std::vector<snek::vector_2f>& snek::player::get_segments() const { return segments; }

void snek::player::update(const snek::vector_2f& head) {
    const snek::vector_2f tail = segments.back();
    for (auto segment = segments.rbegin(); segment != segments.rend();)
        segment->update((++segment)->get_x(), segment->get_y());
    segments[0].update(head.get_x(), head.get_y());
    if (segments_queue > 0) {
        segments.emplace_back(tail);
        segments_queue--;
    }
}

void snek::player::add_segments(uint8_t count) { segments_queue += count; }