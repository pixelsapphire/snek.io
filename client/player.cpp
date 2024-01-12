#include <SFML/Window.hpp>
#include "player.hpp"

snek::player::player() : head(sf::Vector2f(50, 50)) {
    head.setFillColor(sf::Color::Red);
}

void snek::player::update(const sf::Time& delta_time) {
    const float velocity = delta_time.asSeconds() * speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        head.move(sf::Vector2f(0, -1) * velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        head.move(sf::Vector2f(0, 1) * velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        head.move(sf::Vector2f(-1, 0) * velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        head.move(sf::Vector2f(1, 0) * velocity);
}

void snek::player::draw(sf::RenderTarget& target) const {
    target.draw(head);
}

const sf::Vector2f& snek::player::get_position() const {
    return head.getPosition();
}

void snek::player::set_position(float x, float y) {
    head.setPosition({x, y});
}