#include <cmath>
#include <iostream>
#include "game.hpp"
#include "scene_error.hpp"
#include "scene_main.hpp"
#include "scene_nickname.hpp"

snek::game::game() : config("config/c_config.txt"),
                     window(sf::VideoMode(800, 600), "Projekt na sieciuhy", sf::Style::Titlebar | sf::Style::Close),
                     current_scene(welcome_scene()) {
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
}

snek::game::~game() { window.close(); }

void snek::game::set_scene(const std::shared_ptr<snek::scene>& scene) { next_scene = scene; }

std::shared_ptr<snek::scene_nickname> snek::game::welcome_scene() {
    return std::make_shared<snek::scene_nickname>([&](const auto& n) { start(n); });
}

std::shared_ptr<snek::scene_error> snek::game::error_scene(const std::string& message) {
    return std::make_shared<snek::scene_error>(message, [&] { set_scene(welcome_scene()); });
}

void snek::game::launch() {
    frame_clock.restart();
    while (window.isOpen()) {
        const sf::Time delta_time = frame_clock.getElapsedTime();
        frame_clock.restart();
        sf::Event event{};
        while (window.pollEvent(event)) {
            const bool handled = current_scene->handle_event(event);
            if (not handled and event.type == sf::Event::Closed) {
                server.disconnect();
                window.close();
            }
        }
        current_scene->step_frame(window, delta_time);
        window.display();
        window.clear(sf::Color::Black);
        if (next_scene) {
            current_scene = std::move(next_scene);
            next_scene.reset();
        }
    }
}

void snek::game::start(const std::string& player_nickname) {
    std::string error_message;
    if (server.connect(sf::IpAddress(config.get_string("host")), config.get_int("port"))) {
        this->nickname = player_nickname;
        const auto status = server.join(player_nickname);
        if (status == snek::connection_status::connected) {
            const sf::Vector2f spawn_point{100, 100};
            game_clock.restart();
            std::unique_ptr<snek::scene_main> scene = std::make_unique<snek::scene_main>(
                    [&](auto& p) { return player_movement(p); },
                    [&] { return fetch_positions(); });
            scene->spawn_player(nickname, spawn_point, true);
            scene->spawn_player("NPC", sf::Vector2f(200, 200), false);
            set_scene(std::move(scene));
            return;
        }
        if (status == snek::connection_status::game_full) error_message = "The game is full";
        else if (status == snek::connection_status::nickname_taken) error_message = "Nickname is already taken";
        else error_message = "Unknown connection error";
    } else error_message = "Could not connect to the server";
    set_scene(error_scene(error_message));
}

snek::player::state snek::game::player_movement(const sf::Vector2f& velocity) {
    const auto state = server.send_player_velocity(velocity);
    if (not state.alive) set_scene(error_scene("Game over"));
    return state;
}

std::map<std::string, sf::Vector2f> snek::game::fetch_positions() const {
    std::map<std::string, sf::Vector2f> positions{{"NPC", sf::Vector2f(400, 300) + sf::Vector2f(
            150 * std::sin(game_clock.getElapsedTime().asSeconds()),
            100 * std::cos(game_clock.getElapsedTime().asSeconds()))}};
    return positions;
}