#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <string>
#include <map>
#include <utility>
#include "vector_2f.hpp"
#include "utility.hpp"
#include "player.hpp"

#define PLAYER_HEAD_RADIUS 26.0

namespace snek {

    class game {

        std::map<std::string, snek::player> players;

    public:
        bool no_player_nearby(float x, float y, const std::string& nickname) const;

        bool is_alive (const std::string& nickname);

        void add_player(const std::string& nickname);

        void store_player_position(const std::string& nickname, float x, float y);

        std::string get_player_position(const std::string& nickname);

        size_t player_count();

        bool nickname_taken(const std::string& nickname);

        const std::map<std::string, player>& get_players ();
    };

} // snek

#endif //SNEK_IO_GAME_HPP
