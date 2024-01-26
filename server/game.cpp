#include <cmath>
#include <sstream>
#include <string>
#include "common_utility.hpp"
#include "game.hpp"

void snek::game::store_player_position(const std::string& nickname, const snek::vector2f& position) {
    if (not collides(position, nickname)) {
        players.at(nickname).update(position);
        if (hovers_food(position, nickname)) players.at(nickname).add_segments(position);
    } else players.erase(nickname);
}

bool snek::game::is_alive(const std::string& nickname) { return players.contains(nickname); }

void snek::game::add_player(const std::string& nickname) {
    float x, y;
    do {
        x = float(snek::random_value(25, 775));
        y = float(snek::random_value(25, 575));
    } while (collides({x, y}, nickname));
    players.emplace(nickname, player({x, y}));

}

std::string snek::game::get_player_position(const std::string& nickname) {
    return std::to_string(players.at(nickname).get_head().x) + "x" +
           std::to_string(players.at(nickname).get_head().y) + "y";
}

size_t snek::game::player_count() { return players.size(); }

bool snek::game::nickname_taken(const std::string& nickname) { return players.contains(nickname); }

const std::map<std::string, snek::player>& snek::game::get_players() { return players; }

bool snek::game::collides(const snek::vector2f& position, const std::string& nickname) const {
    for (const auto& player : players)
        for (const auto& segment : player.second.get_segments())
            if (nickname != player.first && is_nearby(position, segment, PLAYER_HEAD_RADIUS * 2)) return true;
    return false;
}

void snek::game::move_player(const std::string& nickname, const snek::vector2f& target_velocity, float time) {

    player& player = players.at(nickname);
    if (target_velocity != snek::vector2f::zero) {

        if (player.velocity == snek::vector2f::zero) player.velocity = target_velocity;
        else player.velocity = snek::vector2f::direction_change(player.velocity, target_velocity, 0.05f);

        const snek::vector2f new_position = player.get_head() + player.velocity * time;
        const bool x_bad = new_position.x < 25 or new_position.x > 775,
                y_bad = new_position.y < 25 or new_position.y > 575;

        if (x_bad and y_bad) player.velocity = {0, 0};
        else if (x_bad) player.velocity = {0, player.velocity.y < 0 ? -1 : 1};
        else if (y_bad) player.velocity = {player.velocity.x < 0 ? -1 : 1, 0};

    }
    store_player_position(nickname, player.get_head() + snek::player::speed * player.velocity * time);
}

std::string snek::game::get_player_segments(const std::string& nickname) {
    std::stringstream ss;
    for (auto& segment : players.at(nickname).get_segments()) ss << segment.str();
    return ss.str();
}

void snek::game::remove_player(const std::string& nickname) { players.erase(nickname); }

bool snek::game::hovers_food(const snek::vector2f&, const std::string&) { return false; }
