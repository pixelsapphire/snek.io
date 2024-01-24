#include "game.hpp"
#include <string>
#include <sstream>

void snek::game::store_player_position(const std::string& nickname, const snek::vector_2f& position) {
    if (not collides(position, nickname)) players.at(nickname).update(position);
    else players.erase(nickname);
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
    return std::to_string(players.at(nickname).get_head().get_x()) + "x" +
           std::to_string(players.at(nickname).get_head().get_y()) + "y";
}

size_t snek::game::player_count() { return players.size(); }

bool snek::game::nickname_taken(const std::string& nickname) { return players.contains(nickname); }

const std::map<std::string, snek::player>& snek::game::get_players() { return players; }

bool snek::game::collides(const snek::vector_2f& position, const std::string& nickname) const {
    for (const auto& player : players)
        for (const auto& segment : player.second.get_segments())
            if (nickname != player.first && is_nearby(position, segment, PLAYER_HEAD_RADIUS * 2)) return true;
    return false;
}

void snek::game::move_player(const std::string& nickname, const snek::vector_2f& translation) {
    store_player_position(nickname, players.at(nickname).get_head() + translation);
}

std::string snek::game::get_player_segments(const std::string& nickname) {
    std::stringstream ss;
    for (auto& segment : players.at(nickname).get_segments()) {
        ss << std::to_string(segment.get_x()) << "x" << std::to_string(segment.get_y()) << "y";
    }
    return ss.str();
}

void snek::game::remove_player(const std::string& nickname) {
    players.erase(nickname);
}
