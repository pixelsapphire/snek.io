#include <SFML/Window.hpp>
#include "player.hpp"

snek::player::player() : sf::RectangleShape(sf::Vector2f(50, 50)) {
    setFillColor(sf::Color::Red);
    setPosition(sf::Vector2f(100, 100));
}

void snek::player::update(const sf::Time& delta_time) {
    const float velocity = delta_time.asSeconds() * speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        move(sf::Vector2f(0, -1) * velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        move(sf::Vector2f(0, 1) * velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        move(sf::Vector2f(-1, 0) * velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        move(sf::Vector2f(1, 0) * velocity);
}