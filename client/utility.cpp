#include <sstream>
#include <string>
#include "utility.hpp"

sf::Vector2f snek::conv::to_vec2f(const sf::Event::MouseButtonEvent& ev) { return {float(ev.x), float(ev.y)}; }

bool snek::event::key_pressed(const sf::Event& ev, sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
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

std::vector<sf::Vector2f> snek::serial::decode_vector_array(const std::string& array_data) {
    std::vector<sf::Vector2f> array;
    std::stringstream ss(array_data);
    std::string n, x, y;
    std::getline(ss, n, 'n');
    size_t size = std::stoul(n);
    for (size_t i = 0; i < size; ++i) {
        std::getline(ss, x, 'x'), std::getline(ss, y, 'y');
        array.emplace_back(std::stof(x), std::stof(y));
    }
    return array;
}
