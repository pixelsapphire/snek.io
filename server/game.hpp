#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <map>
#include <optional>
#include <string>
#include <utility>
#include "player.hpp"
#include "utility.hpp"
#include "vector2f.hpp"

#define PLAYER_HEAD_RADIUS 26.0

namespace snek {

    class game {

        std::map<std::string, snek::player> players;

        [[nodiscard]] snek::vector2f player_position(const std::string& nickname);

    public:

        bool is_alive(const std::string& nickname);

        void add_player(const std::string& nickname);

        void store_player_position(const std::string& nickname, const snek::vector2f& position);

        void move_player(const std::string& nickname, const snek::vector2f& target_direction, float time);

        [[nodiscard]] std::string get_player_position_str(const std::string& nickname);

        [[nodiscard]] std::string get_player_segments(const std::string& nickname);

        [[nodiscard]] size_t player_count();

        bool nickname_taken(const std::string& nickname);

        [[nodiscard]] const std::map<std::string, player>& get_players();

        [[nodiscard]] std::optional<std::string> collides(const snek::vector2f& position,
                                                          const std::string& nickname) const;

        void remove_player(const std::string& nickname);

        [[nodiscard]] bool hovers_food(const snek::vector2f& position, const std::string& nickname);
    };

}

#endif //SNEK_IO_GAME_HPP
