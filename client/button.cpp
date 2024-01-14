#include "assets.hpp"
#include "button.hpp"
#include "utility.hpp"

snek::button::button(const std::string& text) {
    this->text.setFont(snek::assets::get_font());
    this->text.setCharacterSize(36);
    this->text.setFillColor(sf::Color::White);
    this->text.setString(text);
    const auto text_bounds = this->text.getLocalBounds();
    const auto size = sf::Vector2f(text_bounds.width + 60, text_bounds.height + 30);
    this->text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
    this->border.setSize(size);
    this->border.setFillColor(sf::Color::Transparent);
    this->border.setOutlineColor(sf::Color::White);
    this->border.setOutlineThickness(4);
    this->border.setOrigin(size.x / 2, size.y / 3);
}

bool snek::button::contains(const sf::Vector2f& point) const { return border.getGlobalBounds().contains(point); }

bool snek::button::contains(const sf::Event::MouseButtonEvent& point) const {
    return border.getGlobalBounds().contains(snek::conv::to_vec2f(point));
}

void snek::button::draw(sf::RenderTarget& target) const {
    target.draw(border);
    target.draw(text);
}

const sf::Vector2f& snek::button::get_position() const { return border.getPosition(); }

void snek::button::set_position(float x, float y) {
    border.setPosition(x, y);
    text.setPosition(x, y);
}