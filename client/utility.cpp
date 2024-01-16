#include "utility.hpp"

sf::Vector2f snek::conv::to_vec2f(const sf::Event::MouseButtonEvent& ev) { return {float(ev.x), float(ev.y)}; }

bool snek::event::key_pressed(const sf::Event& ev, sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}