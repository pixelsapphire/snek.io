#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace snek {

    class game {

        sf::RenderWindow window;
        sf::Clock clock;
        std::unique_ptr<snek::scene> current_scene;
        std::string nickname;

    public:

        game();

        ~game();

        void launch();

        void start(const std::string& player_nickname);

        void player_movement(const sf::Vector2f& position) const;
    };
}

#endif //SNEK_IO_GAME_HPP
