#include "game.hpp"
#include "scene_main.hpp"
#include "scene_nickname.hpp"

snek::game::game() : window(sf::VideoMode(800, 600), "Projekt na sieciuhy"),
                     current_scene(std::make_unique<snek::scene_nickname>([&](const auto& n) { this->start(n); })) {
    window.setFramerateLimit(60);
}

snek::game::~game() {
    window.close();
}

void snek::game::launch() {
    clock.restart();
    while (window.isOpen()) {
        const sf::Time delta_time = clock.getElapsedTime();
        clock.restart();
        sf::Event event{};
        while (window.pollEvent(event)) {
            const bool handled = current_scene->handle_event(event);
            if (not handled and event.type == sf::Event::Closed) window.close();
        }
        current_scene->step_frame(window, delta_time);
        window.display();
        window.clear(sf::Color::Black);
    }
}

void snek::game::start(const std::string& nickname) {
    this->nickname = nickname;
    current_scene = std::make_unique<snek::scene_main>();
}