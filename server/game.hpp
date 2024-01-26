#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <map>
#include <string>
#include <utility>
#include "vector2f.hpp"
#include "utility.hpp"
#include "player.hpp"

#define PLAYER_HEAD_RADIUS 26.0

namespace snek {

    class game {

        std::map<std::string, snek::player> players;

    public:

        bool is_alive(const std::string& nickname);

        void add_player(const std::string& nickname);

        void store_player_position(const std::string& nickname, const snek::vector2f& position);

        void move_player(const std::string& nickname, const snek::vector2f& target_direction, float time);

        std::string get_player_position(const std::string& nickname);

        std::string get_player_segments(const std::string& nickname);

        size_t player_count();

        bool nickname_taken(const std::string& nickname);

        const std::map<std::string, player>& get_players();

        [[nodiscard]] bool collides(const snek::vector2f& position, const std::string& nickname) const;

        void remove_player(const std::string& nickname);

        [[nodiscard]] bool hovers_food(const snek::vector2f& position, const std::string& nickname);
    };

}

#endif //SNEK_IO_GAME_HPP
