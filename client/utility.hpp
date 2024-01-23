#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <map>
#include <set>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace snek {
    namespace conv {
        [[nodiscard]] sf::Vector2f to_vec2f(const sf::Event::MouseButtonEvent& ev);
    }
    namespace event {
        [[nodiscard]] bool key_pressed(const sf::Event& ev, sf::Keyboard::Key key);
    }
    namespace factory {
        template<typename T>
        [[nodiscard]] std::set<T> range_set(T begin, T end) {
            std::set<T> result;
            for (T i = begin; i < end; ++i) result.insert(i);
            return result;
        }
    }
    namespace serial {

        [[nodiscard]] sf::Vector2f decode_vector(const std::string& vector_data);

        [[nodiscard]] std::string encode_vector(const sf::Vector2f& vector);

        [[nodiscard]] std::map<std::string, sf::Vector2f> decode_players(const std::string& players_data);
    }
}

template<typename T>
std::set<T> operator-(const std::set<T>& lhs, const std::set<T>& rhs) {
    std::set<T> result;
    std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(result, result.begin()));
    return result;
}

#endif //SNEK_IO_UTILITY_HPP
