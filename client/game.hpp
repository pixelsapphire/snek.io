#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"

namespace snek {

    class game {

        sf::RenderWindow window;
        sf::Clock clock;
        snek::player player;

    public:

        game();

        ~game();

        void run();
    };
}

#endif //SNEK_IO_GAME_HPP
