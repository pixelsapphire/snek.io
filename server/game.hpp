#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <string>
#include <map>
#include <utility>
#include "vector_2f.hpp"
#include "utility.hpp"

namespace snek {

    class game {

        std::map<std::string, vector_2f> players;

    public:

        bool is_alive (const std::string& nickname);

        void add_player(const std::string& nickname);

        void store_player_position(const std::string& nickname, float x, float y);

        std::string get_player_position(const std::string& nickname);

        size_t player_count();

        bool nickname_taken(const std::string& nickname);

        const std::map<std::string, vector_2f>& get_players ();
    };

} // snek

#endif //SNEK_IO_GAME_HPP
