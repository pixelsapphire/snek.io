#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include <cstdint>
#include <vector>
#include "vector_2f.hpp"
#include <optional>

#define LEAST_SEGMENT_DISTANCE 12.5f

namespace snek {

    class player {

        std::vector<vector_2f> segments;
        uint8_t segments_queue = 5;
        std::optional<vector_2f> place_4_new_segment;

    public:

        explicit player(const snek::vector_2f& position);

        void update(const snek::vector_2f& head);

        [[nodiscard]] const snek::vector_2f& get_head();

        [[nodiscard]] const std::vector<snek::vector_2f>& get_segments() const;

        void add_segments(const vector_2f& position, uint8_t count = 1);

    };

} // snek

#endif //SNEK_IO_PLAYER_HPP
