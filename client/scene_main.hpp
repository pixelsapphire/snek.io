#ifndef SNEK_IO_SCENE_MAIN_HPP
#define SNEK_IO_SCENE_MAIN_HPP

#include <functional>
#include <memory>
#include "scene.hpp"
#include "player.hpp"

namespace snek {

    class scene_main : public snek::scene {

        std::shared_ptr<snek::player> client_player;
        std::function<void(const sf::Vector2f& position)> player_moved;

    public:

        explicit scene_main(const std::function<void(const sf::Vector2f& position)>& on_player_movement);

        void spawn_player(const std::string& nickname, const sf::Vector2f& position, bool client = true);

        void update(const sf::Time& delta_time) override;
    };
}

#endif //SNEK_IO_SCENE_MAIN_HPP
