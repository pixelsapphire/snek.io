#include "game.hpp"
#include <string>

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
    players.emplace(nickname, vector_2f(snek::random_value(25,775), snek::random_value(25,575)));
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
