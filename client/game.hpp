#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace snek {

    class game {

        sf::RenderWindow window;
        sf::Clock game_clock, frame_clock;
        std::unique_ptr<snek::scene> current_scene;
        std::string nickname;

    public:

        game();

        ~game();

        void launch();

        void start(const std::string& player_nickname);

        void player_movement(const sf::Vector2f& position) const;

        std::map<std::string, sf::Vector2f> fetch_positions() const;
    };
}

#endif //SNEK_IO_GAME_HPP
