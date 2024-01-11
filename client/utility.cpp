#include "utility.hpp"

sf::Vector2f snek::conv::to_vec2f(const sf::Event::MouseButtonEvent& ev) {
    return sf::Vector2f(ev.x, ev.y);
}