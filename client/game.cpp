#include "game.hpp"

snek::game::game() : window(sf::VideoMode(sf::Vector2u(800, 600)), "Projekt na sieciuhy") {
    window.setFramerateLimit(60);
}

snek::game::~game() {
    window.close();
}

void snek::game::run() {
    clock.restart();
    while (window.isOpen()) {
        const sf::Time delta_time = clock.getElapsedTime();
        clock.restart();
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        player.update(delta_time);
        window.draw(player);
        window.display();
        window.clear(sf::Color::Black);
    }
}