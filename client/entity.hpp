#ifndef SNEK_IO_ENTITY_HPP
#define SNEK_IO_ENTITY_HPP

#include <SFML/Graphics.hpp>

namespace snek {

    class entity {

    public:

        virtual void update(const sf::Time& delta_time) = 0;

        virtual void draw(sf::RenderTarget& target) = 0;

        virtual void set_position(float x, float y) = 0;
    };
}

#endif //SNEK_IO_ENTITY_HPP
