#include "assets.hpp"

namespace snek::assets {

    const sf::Font& get_font() {
        static sf::Font font;
        if (font.getInfo().family.empty() and not font.loadFromFile("assets/font/jetbrains_mono.ttf"))
            throw std::runtime_error("Failed to load assets");
        return font;
    }
}