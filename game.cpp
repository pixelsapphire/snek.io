#include "game.hpp"

game::game() : sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "Projekt na sieciuhy") {
    setFramerateLimit(60);
}

game::~game() {
    sf::Window::close();
}

void game::run() {
    clock.restart();
    while (isOpen()) {
        const sf::Time delta_time = clock.getElapsedTime();
        clock.restart();
        sf::Event event{};
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) close();
        }
        player.update(delta_time);
        draw(player);
        display();
        clear(sf::Color::Black);
    }
}