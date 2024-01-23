//
// Created by stas on 23.01.2024.
//

#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include "vector_2f.hpp"
#include <vector>

namespace snek {

    class player {

        std::vector<vector_2f> segments;


    public:

        player(float x, float y);

        void update (float x_head, float y_head);

        const vector_2f& get_head ();

        [[nodiscard]] const std::vector<vector_2f> get_segments() const;
    };

} // snek

#endif //SNEK_IO_PLAYER_HPP
