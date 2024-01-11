#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace snek {

    class player : public snek::entity {

        float speed = 100;
        sf::RectangleShape head;

    public:

        player();

        void update(const sf::Time& delta_time) override;

        void draw(sf::RenderTarget& target) override;

        void set_position(float x, float y) override;
    };
}

#endif //SNEK_IO_PLAYER_HPP
