#include "player.hpp"
#include "utility.hpp"

snek::player::player(const snek::vector2f& position) {
    segments.emplace_back(position);
    new_segment = position;
    offset = 0.0f;
    segments_queue = 4;
}

const snek::vector2f& snek::player::get_head() const { return segments[0]; }

const std::vector<snek::vector2f>& snek::player::get_segments() const { return segments; }

void snek::player::update_segments() {
    const snek::vector2f tail = snek::vector2f(segments.back());
    for (auto segment = segments.rbegin(); segment != segments.rend() - 1; ++segment) *segment = *(segment + 1);

    if (segments_queue > 0) {
        segments.emplace_back(tail);
        if (--segments_queue == 0) new_segment.reset();
    }
}

void snek::player::update(const snek::vector2f& head) {

    if(get_offset() > SEGMENT_DISTANCE) {
        set_offset(get_offset() - SEGMENT_DISTANCE);
        update_segments();
    }

    segments[0] = head;
}

void snek::player::add_segments(uint8_t count) {
    if (segments_queue == 0) new_segment = segments.back();
    segments_queue += count;
}

float snek::player::get_offset() const { return offset; }

void snek::player::set_offset(float new_offset) { offset = new_offset; }

