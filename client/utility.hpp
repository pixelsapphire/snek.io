#ifndef SNEK_IO_UTILITY_HPP
#define SNEK_IO_UTILITY_HPP

#include <set>
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
}

template<typename T>
std::set<T> operator-(const std::set<T>& lhs, const std::set<T>& rhs) {
    std::set<T> result;
    std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(result, result.begin()));
    return result;
}

#endif //SNEK_IO_UTILITY_HPP
