#ifndef PROJEKT_GAME_HPP
#define PROJEKT_GAME_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"

class game : sf::RenderWindow {

    sf::Clock clock;
    player player;

public:

    game();

    ~game();

    void run();
};


#endif //PROJEKT_GAME_HPP
