#include <cmath>
#include "scene_main.hpp"

snek::scene_main::scene_main(const std::function<snek::player::state(const sf::Vector2f& position)>& on_player_movement,
                             const std::function<std::map<std::string, sf::Vector2f>()>& positions_provider)
        : player_moved(on_player_movement), fetch_positions(positions_provider) {}

void snek::scene_main::spawn_player(const std::string& nickname, const sf::Vector2f& position, bool client) {
    auto player = std::make_shared<snek::player>(nickname);
    player->set_position(position.x, position.y);
    add(player);
    if (client) client_player = player;
    else other_players[nickname] = player;
}

void snek::scene_main::remove_player(const std::string& nickname) {
    remove(other_players[nickname]);
    other_players.erase(nickname);
}

void snek::scene_main::update(const sf::Time& delta_time) {
    snek::scene::update(delta_time);
    sf::Vector2f offset;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) offset += sf::Vector2f(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) offset += sf::Vector2f(0, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) offset += sf::Vector2f(-1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) offset += sf::Vector2f(1, 0);
    if (offset.x != 0 and offset.y != 0) offset /= std::sqrt(2.f);
    const auto state = player_moved(offset * snek::player::speed);
    client_player->set_state(state);
    const auto& positions = fetch_positions();
    for (const auto& [nickname, player] : other_players)
        player->set_position(positions.at(nickname).x, positions.at(nickname).y);
}