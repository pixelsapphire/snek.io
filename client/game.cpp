#include "game.hpp"
#include "scene_main.hpp"

snek::game::game() : window(sf::VideoMode(sf::Vector2u(800, 600)), "Projekt na sieciuhy"),
                     current_scene(std::make_unique<snek::scene_main>()) {
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
        current_scene->update(window, delta_time);
        window.display();
        window.clear(sf::Color::Black);
    }
}