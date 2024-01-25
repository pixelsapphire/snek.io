#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "scene.hpp"
#include "scene_error.hpp"
#include "scene_nickname.hpp"
#include "server_handler.hpp"

namespace snek {

    class game {

        snek::config config;
        snek::server_handler server;
        sf::RenderWindow window;
        sf::Clock game_clock, frame_clock;
        std::shared_ptr<snek::scene> current_scene, next_scene;
        std::string nickname;

        void set_scene(const std::shared_ptr<snek::scene>& scene);

        [[nodiscard]] std::shared_ptr<snek::scene_nickname> welcome_scene();

        [[nodiscard]] std::shared_ptr<snek::scene_error> error_scene(const std::string& message);

    public:

        game();

        ~game();

        void launch();

        void start(const std::string& player_nickname);

        snek::player::state player_movement(const sf::Vector2f& velocity);

        [[nodiscard]] std::map<std::string, snek::player::state> fetch_positions();
    };
}

#endif //SNEK_IO_GAME_HPP
