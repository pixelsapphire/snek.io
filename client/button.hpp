#ifndef SNEK_IO_BUTTON_HPP
#define SNEK_IO_BUTTON_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace snek {

    class button : public snek::entity {

        sf::Text text;
        sf::RectangleShape border;

        [[nodiscard]] bool contains(const sf::Event::MouseButtonEvent& point) const;

    public:

        explicit button(const std::string& text);

        [[nodiscard]] bool clicked(const sf::Event& event) const;

        void draw(sf::RenderTarget& target) const override;

        [[nodiscard]] const sf::Vector2f& get_position() const override;

        void set_position(float x, float y) override;
    };
}

#endif //SNEK_IO_BUTTON_HPP