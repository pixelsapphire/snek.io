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

void snek::game::move_player(const std::string& nickname, const snek::vector2f& target_direction, float time) {

    player& player = players.at(nickname);
    const float offset = snek::player::speed * time;
    const auto future_position = [&] { return player.get_head() + player.direction * offset; };

    if (target_direction != snek::vector2f::zero) {
        if (player.direction == snek::vector2f::zero) player.direction = target_direction;
        else player.direction = snek::vector2f::direction_change(player.direction, target_direction, 0.05f);
    }

    const snek::vector2f expected = future_position();
    const bool bad_x = expected.x < 25 or expected.x > 775, bad_y = expected.y < 25 or expected.y > 575;
    if (bad_x) player.direction = {0, snek::sgn(player.direction.y)};
    if (bad_y) player.direction = {snek::sgn(player.direction.x), 0};

    player.direction = player.direction.normalized();
    store_player_position(nickname, future_position());
}

std::string snek::game::get_player_segments(const std::string& nickname) {
    std::stringstream ss;
    for (auto& segment : players.at(nickname).get_segments()) ss << segment.str();
    return ss.str();
}

void snek::game::remove_player(const std::string& nickname) { players.erase(nickname); }

bool snek::game::hovers_food(const snek::vector2f&, const std::string&) { return false; }
