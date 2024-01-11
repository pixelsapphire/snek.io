#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace snek::conv {
    sf::Vector2f to_vec2f(const sf::Event::MouseButtonEvent& ev);
}

#endif //SNEK_IO_UTILITY_HPP
