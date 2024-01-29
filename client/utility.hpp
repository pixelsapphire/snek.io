#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <map>
#include <set>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace snek {
    namespace conv {
        [[nodiscard]] sf::Vector2f to_vec2f(const sf::Event::MouseButtonEvent& ev);
    }
    namespace event {
        [[nodiscard]] bool key_pressed(const sf::Event& ev, sf::Keyboard::Key key);
    }
    namespace serial {

        [[nodiscard]] sf::Vector2f decode_vector(const std::string& vector_data);

        [[nodiscard]] std::string encode_vector(const sf::Vector2i& vector);

        [[nodiscard]] std::vector<sf::Vector2f> decode_vector_array(const std::string& array_data);
    }
}

#endif //SNEK_IO_UTILITY_HPP
