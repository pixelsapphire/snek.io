#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include <SFML/Graphics.hpp>

namespace snek {

    class player : public sf::RectangleShape {

        float speed = 100;

    public:

        player();

        void update(const sf::Time& delta_time);
    };
}

#endif //SNEK_IO_PLAYER_HPP
