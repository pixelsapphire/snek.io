#include "player.hpp"
#include "utility.hpp"

snek::player::player(const snek::vector2f& position) {
    segments.emplace_back(position);
    new_segment = position;
}

const snek::vector2f& snek::player::get_head() const { return segments[0]; }

const std::vector<snek::vector2f>& snek::player::get_segments() const { return segments; }

void snek::player::update(const snek::vector2f& head) {

    const snek::vector2f tail = snek::vector2f(segments.back());
    for (auto segment = segments.rbegin(); segment != segments.rend() - 1; ++segment) *segment = *(segment + 1);
    segments[0] = head;

    if (segments_queue > 0 and not is_nearby(*new_segment, segments.back(), LEAST_SEGMENT_DISTANCE)) {
        segments.emplace_back(tail);
        if (--segments_queue == 0) new_segment.reset();
    }
}

void snek::player::add_segments(uint8_t count) {
    if (segments_queue == 0) new_segment = segments.back();
    segments_queue += count;
}
