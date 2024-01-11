#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace snek {

    class game {

        sf::RenderWindow window;
        sf::Clock clock;
        std::unique_ptr<snek::scene> current_scene;

    public:

        game();

        ~game();

        void run();
    };
}

#endif //SNEK_IO_GAME_HPP
