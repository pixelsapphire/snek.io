#include <cmath>
#include <sstream>
#include <string>
#include "common_utility.hpp"
#include "utility.hpp"

sf::Vector2f snek::conv::to_vec2f(const sf::Event::MouseButtonEvent& ev) { return {float(ev.x), float(ev.y)}; }

bool snek::event::key_pressed(const sf::Event& ev, sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}

sf::Vector2f snek::math::direction_change(const sf::Vector2f& origin, const sf::Vector2f& target, float delta_max) {
    float delta = __clang_std::atan2f(target.y, target.x) - __clang_std::atan2f(origin.y, origin.x);
    if (delta > M_PI) delta -= 2 * M_PI;
    else if (delta < -M_PI) delta += 2 * M_PI;
    delta = std::clamp(delta, -delta_max, delta_max);
    return {origin.x * __clang_std::cosf(delta) - origin.y * __clang_std::sinf(delta),
            origin.x * __clang_std::sinf(delta) + origin.y * __clang_std::cosf(delta)};
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
