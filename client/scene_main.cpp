#include "scene_main.hpp"

snek::scene_main::scene_main() {
    auto player = std::make_shared<snek::player>();
    player->set_position(100, 100);
    add(player);
}