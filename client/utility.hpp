#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace snek {
    namespace conv {
        [[nodiscard]] sf::Vector2f to_vec2f(const sf::Event::MouseButtonEvent& ev);
    }
    namespace event {
        [[nodiscard]] bool key_pressed(const sf::Event& ev, sf::Keyboard::Key key);
    }
}

#endif //SNEK_IO_UTILITY_HPP
