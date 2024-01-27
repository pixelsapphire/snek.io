#include "assets.hpp"
#include "common_utility.hpp"

const std::string& snek::assets::path() {
    static const std::string path = snek::get_executable_path() + "/assets";
    return path;
}

const sf::Font& snek::assets::get_font() {
    static sf::Font font;
    if (font.getInfo().family.empty() and not font.loadFromFile(snek::assets::path() + "/font/jetbrains_mono.ttf"))
        throw std::runtime_error("Failed to load assets");
    return font;
}
