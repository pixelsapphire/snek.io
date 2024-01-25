#include <cmath>
#include <sstream>
#include <string>
#include "utility.hpp"

sf::Vector2f snek::conv::to_vec2f(const sf::Event::MouseButtonEvent& ev) { return {float(ev.x), float(ev.y)}; }

bool snek::event::key_pressed(const sf::Event& ev, sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}

sf::Vector2f snek::math::direction_change(const sf::Vector2f& origin, const sf::Vector2f& target, float delta_max) {
    float delta = atan2f(target.y, target.x) - atan2f(origin.y, origin.x);
    if (delta > M_PI) delta -= 2 * M_PI;
    else if (delta < -M_PI) delta += 2 * M_PI;
    delta = std::clamp(delta, -delta_max, delta_max);
    return {origin.x * cosf(delta) - origin.y * sinf(delta),
            origin.x * sinf(delta) + origin.y * cosf(delta)};
}

sf::Vector2f snek::serial::decode_vector(const std::string& vector_data) {
    std::stringstream ss(vector_data);
    std::string x, y;
    std::getline(ss, x, 'x'), std::getline(ss, y, 'y');
    return {std::stof(x), std::stof(y)};
}

std::string snek::serial::encode_vector(const sf::Vector2f& vector) {
    return std::to_string(vector.x) + "x" + std::to_string(vector.y) + "y";
}
