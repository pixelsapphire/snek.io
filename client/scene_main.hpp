#ifndef SNEK_IO_SCENE_MAIN_HPP
#define SNEK_IO_SCENE_MAIN_HPP

#include <functional>
#include <map>
#include <memory>
#include "scene.hpp"
#include "player.hpp"

namespace snek {

    class scene_main : public snek::scene {

        std::shared_ptr<snek::player> client_player;
        sf::Vector2f player_angle;
        std::map<std::string, std::shared_ptr<snek::player>> other_players;
        std::function<snek::player::state(const sf::Vector2f& position)> player_moved;
        std::function<std::map<std::string, sf::Vector2f>()> fetch_positions;

    public:

        scene_main(const std::function<snek::player::state(const sf::Vector2f& position)>& on_player_movement,
                   const std::function<std::map<std::string, sf::Vector2f>()>& positions_provider);

        void spawn_player(const std::string& nickname, bool client = true);

        void remove_player(const std::string& nickname);

        void update(const sf::Time& delta_time) override;
    };
}

#endif //SNEK_IO_SCENE_MAIN_HPP
