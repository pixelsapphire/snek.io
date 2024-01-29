#include <algorithm>
#include <sstream>
#include <string>
#include "game.hpp"

void snek::game::store_player_position(const std::string& nickname, const snek::vector2f& position) {
    const auto collided_player = collides(position, nickname);
    if (collided_player.has_value()) {
        if (snek::is_nearby(position, player_position(*collided_player), 2 * PLAYER_HEAD_RADIUS))
            players.erase(*collided_player);
        players.erase(nickname);
    }
    else {
        players.at(nickname).update(position);
        if (hovers_food(position, nickname)) players.at(nickname).add_segments(position);
    }
}

bool snek::game::is_alive(const std::string& nickname) const { return players.contains(nickname); }

void snek::game::add_player(const std::string& nickname) {
    float x, y;
    do {
        x = float(snek::random_value(25, 775));
        y = float(snek::random_value(25, 575));
    }
    while (collides({x, y}, nickname));
    players.emplace(nickname, player({x, y}));

}

snek::vector2f snek::game::player_position(const std::string& nickname) const { return players.at(nickname).get_head(); }

std::string snek::game::player_position_str(const std::string& nickname) const {
    const auto position = player_position(nickname);
    return std::to_string(position.x) + "x" + std::to_string(position.y) + "y";
}

size_t snek::game::player_count() const { return players.size(); }

bool snek::game::nickname_taken(const std::string& nickname) const { return players.contains(nickname); }

const std::map<std::string, snek::player>& snek::game::get_players() { return players; }

std::optional<std::string> snek::game::collides(const snek::vector2f& position, const std::string& player) const {
    for (const auto& [nickname, snake] : players)
        for (const auto& segment : snake.get_segments())
            if (player != nickname and is_nearby(position, segment, PLAYER_HEAD_RADIUS * 2)) return nickname;
    return std::nullopt;
}

void snek::game::move_player(const std::string& nickname, const snek::vector2f& target_direction, float time) {

    player& player = players.at(nickname);
    const float offset = snek::player::speed * time;
    const float epsillon = 1.0f;
    const auto future_position = [&] { return player.get_head() + player.direction * offset; };

    if (target_direction != snek::vector2f::zero) {
        if (player.direction == snek::vector2f::zero) player.direction = target_direction;
        else player.direction = snek::vector2f::direction_change(player.direction, target_direction, 0.05f);
    }

    snek::vector2f expected = future_position();
    const bool bad_x = expected.x < 25 or expected.x > 775, bad_y = expected.y < 25 or expected.y > 575;

    if (bad_x and bad_y) player.direction = {0, 0};
    else if (bad_y) {
        if (expected.x - epsillon < 25) { player.direction = {1, 0}; }
        else if (expected.x + epsillon > 775) { player.direction = {-1, 0}; }
        else player.direction = {snek::sgn(player.direction.x, player.direction.x > 400 ? -1 : 1), 0};
    }
    else if (bad_x) {
        if (expected.y - epsillon < 25) { player.direction = {0, 1}; }
        else if (expected.y + epsillon > 575) { player.direction = {0, -1}; }
        else player.direction = {0, snek::sgn(player.direction.y, player.direction.y > 300 ? -1 : 1)};
    }

    player.direction = player.direction.normalized();
    expected = future_position();
    store_player_position(nickname, {std::clamp(expected.x, 25.0f, 775.0f), std::clamp(expected.y, 25.0f, 575.0f)});
}

std::string snek::game::get_player_segments(const std::string& nickname) const {
    std::stringstream ss;
    for (auto& segment : players.at(nickname).get_segments()) ss << segment.str();
    return ss.str();
}

void snek::game::remove_player(const std::string& nickname) { players.erase(nickname); }

bool snek::game::hovers_food(const snek::vector2f&, const std::string&) { return false; }
