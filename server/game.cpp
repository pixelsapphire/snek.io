#include "game.hpp"
#include <string>
#include <cmath>

void snek::game::store_player_position(const std::string& nickname, float x, float y) {
//    if(players.contains(nickname))
//        players.at(nickname).update(x,y);
//    else players.emplace(nickname, vector_2f(x,y));
    players.at(nickname).update(x,y);
}

bool snek::game::is_alive(const std::string& nickname) {
    return players.contains(nickname);
}

void snek::game::add_player(const std::string &nickname) {
    float x, y;
    do {
        x = float(snek::random_value(25,775));
        y = float(snek::random_value(25,575));
    } while (this->no_player_nearby(x, y));
    players.emplace(nickname, vector_2f(x, y));
}

std::string snek::game::get_player_position(const std::string &nickname) {
    return std::to_string(players.at(nickname).get_x()) + "x" + std::to_string(players.at(nickname).get_y()) + "y";
}

size_t snek::game::player_count() {
    return players.size();
}

bool snek::game::nickname_taken(const std::string &nickname) {
    return !players.contains(nickname);
}

const std::map<std::string,snek::vector_2f> &snek::game::get_players() {
    return players;
}

bool snek::game::no_player_nearby(float x, float y) const {

    auto is_nearby = [&](float x, float y, float xs, float ys, float r) {
        float length = std::pow(x - xs, 2) + std::pow(y - ys, 2);
        return length <= std::pow(r, 2);
    };

    for(const auto& player : players) {
        if(is_nearby(x, y, player.second.get_x(), player.second.get_y(), 26.0))
            return false;
    }
    return true;
}