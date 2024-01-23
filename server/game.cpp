#include "game.hpp"
#include <string>
#include <cmath>

void snek::game::store_player_position(const std::string& nickname, const snek::vector_2f& position) {
    if (no_player_nearby(position, nickname)) players.at(nickname).update(position);
    else players.erase(nickname);
}

bool snek::game::is_alive(const std::string& nickname) { return players.contains(nickname); }

void snek::game::add_player(const std::string& nickname) {
    float x, y;
    do {
        x = float(snek::random_value(25, 775));
        y = float(snek::random_value(25, 575));
    } while (!this->no_player_nearby({x, y}, nickname));
    players.emplace(nickname, player({x, y}));
}

std::string snek::game::get_player_position(const std::string& nickname) {
    return std::to_string(players.at(nickname).get_head().get_x()) + "x" +
           std::to_string(players.at(nickname).get_head().get_y()) + "y";
}

size_t snek::game::player_count() { return players.size(); }

bool snek::game::nickname_taken(const std::string& nickname) { return players.contains(nickname); }

const std::map<std::string, snek::player>& snek::game::get_players() { return players; }

bool snek::game::no_player_nearby(const snek::vector_2f& position, const std::string& nickname) const {

    auto is_nearby = [&](const snek::vector_2f& position, const snek::vector_2f& segment, float r) {
        float length = std::powf(position.get_x() - segment.get_x(), 2) +
                       std::powf(position.get_y() - segment.get_y(), 2);
        return length <= std::powf(r, 2);
    };

    for (const auto& player : players)
        for (const auto& segment : player.second.get_segments())
            if (nickname != player.first && is_nearby(position, segment, PLAYER_HEAD_RADIUS * 2)) return false;

    return true;
}
