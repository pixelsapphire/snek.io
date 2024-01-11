#ifndef PROJEKT_PLAYER_HPP
#define PROJEKT_PLAYER_HPP

#include <SFML/Graphics.hpp>

class player : public sf::RectangleShape {

    float speed = 100;

public:

    player();

    void update(const sf::Time& delta_time);
};


#endif //PROJEKT_PLAYER_HPP
