#include <cmath>
#include <iostream>
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
    frame_clock.restart();
    while (window.isOpen()) {
        const sf::Time delta_time = frame_clock.getElapsedTime();
        frame_clock.restart();
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

void snek::game::start(const std::string& player_nickname) {
    game_clock.restart();
    this->nickname = player_nickname;
    std::unique_ptr<snek::scene_main> scene = std::make_unique<snek::scene_main>(
            [&](auto& p) { player_movement(p); },
            [&] { return fetch_positions(); });
    scene->spawn_player(nickname, sf::Vector2f(100, 100), true);
    scene->spawn_player("NPC", sf::Vector2f(200, 200), false);
    current_scene = std::move(scene);
}

void snek::game::player_movement(const sf::Vector2f& position) const {
    std::cout << "Player moved to " << position.x << ", " << position.y << std::endl;
}

std::map<std::string, sf::Vector2f> snek::game::fetch_positions() const {
    std::map<std::string, sf::Vector2f> positions{{"NPC", sf::Vector2f(400, 300) + sf::Vector2f(
            150 * std::sin(game_clock.getElapsedTime().asSeconds()),
            100 * std::cos(game_clock.getElapsedTime().asSeconds()))}};
    return positions;
}