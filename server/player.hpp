#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include <cstdint>
#include <vector>
#include "vector2f.hpp"
#include <optional>

#define LEAST_SEGMENT_DISTANCE 12.5f

namespace snek {

    class player {

        std::vector<snek::vector2f> segments;
        uint8_t segments_queue = 5;
        std::optional<snek::vector2f> new_segment;

    public:

        constexpr inline static float speed = 100.0f;

        snek::vector2f direction;

        explicit player(const snek::vector2f& position);

        void update(const snek::vector2f& head);

        [[nodiscard]] const snek::vector2f& get_head();

        [[nodiscard]] const std::vector<snek::vector2f>& get_segments() const;

        void add_segments(const vector2f& position, uint8_t count = 1);

    };

} // snek

#endif //SNEK_IO_PLAYER_HPP
