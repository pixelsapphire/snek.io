#ifndef SNEK_IO_GAME_HPP
#define SNEK_IO_GAME_HPP

#include <map>
#include <optional>
#include <string>
#include <utility>
#include "player.hpp"
#include "utility.hpp"
#include "vector2f.hpp"

#define PLAYER_HEAD_RADIUS 25
#define FOOD_RADIUS 5
#define FOOD_PER_PLAYER 5

namespace snek {

    class game {

        std::map<std::string, snek::player> players;
        std::vector<snek::vector2f> food;

        [[nodiscard]] snek::vector2f get_new_random_position(float radius, const std::string& nickname = "") const;

        [[nodiscard]] snek::vector2f player_position(const std::string& nickname) const;

        [[nodiscard]] bool food_at(const snek::vector2f& position, float object_radius) const;

        uint8_t remove_eaten_food(const std::string& nickname);

        void spawn_food();

    public:

        bool is_alive(const std::string& nickname) const;

        void add_player(const std::string& nickname);

        void remove_player(const std::string& nickname);

        void store_player_position(const std::string& nickname, const snek::vector2f& position);

        void move_player(const std::string& nickname, const snek::vector2f& target_direction, float time);

        [[nodiscard]] std::string player_position_str(const std::string& nickname) const;

        [[nodiscard]] std::string get_player_segments(const std::string& nickname) const;

        [[nodiscard]] size_t player_count() const;

        [[nodiscard]] bool nickname_taken(const std::string& nickname) const;

        [[nodiscard]] const std::map<std::string, player>& get_players();

        [[nodiscard]] std::optional<std::string> collides(const snek::vector2f& position,
                                                          const std::string& nickname) const;

        [[nodiscard]] std::string get_food_str() const;
    };

}

#endif //SNEK_IO_GAME_HPP
