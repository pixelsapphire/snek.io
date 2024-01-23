#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "scene_error.hpp"
#include "scene_nickname.hpp"
#include "server_handler.hpp"

namespace snek {

    class game {

        snek::server_handler server;
        sf::RenderWindow window;
        sf::Clock game_clock, frame_clock;
        std::unique_ptr<snek::scene> current_scene;
        std::string nickname;

        [[nodiscard]] std::unique_ptr<snek::scene_nickname> welcome_scene();

        [[nodiscard]] std::unique_ptr<snek::scene_error> error_scene(const std::string& message);

    public:

        game();

        ~game();

        void launch();

        void start(const std::string& player_nickname);

        void player_movement(const sf::Vector2f& position);

        [[nodiscard]] std::map<std::string, sf::Vector2f> fetch_positions() const;
    };
}

#endif //SNEK_IO_GAME_HPP
