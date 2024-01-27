#ifndef SNEK_IO_ASSETS_HPP
#define SNEK_IO_ASSETS_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace snek::assets {

    const std::string& path();

    const sf::Font& get_font();
}

#endif //SNEK_IO_ASSETS_HPP
