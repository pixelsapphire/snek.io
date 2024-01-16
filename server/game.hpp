#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <string>

namespace snek {

    class game {

    public:

        void store_player_position(const std::string& nickname, float x, float y);

    };

} // snek

#endif //SNEK_IO_GAME_HPP
