#include "scene_main.hpp"
#include "utility.hpp"

snek::scene_main::scene_main(const std::function<snek::player::state(const sf::Vector2f& position)>& on_player_movement,
                             const std::function<std::map<std::string, snek::player::state>()>& positions_provider)
        : player_moved(on_player_movement), fetch_positions(positions_provider) {}

void snek::scene_main::spawn_player(const std::string& nickname, bool client) {
    auto player = std::make_shared<snek::player>(nickname);
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
    sf::Vector2f target_angle;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) target_angle.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) target_angle.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) target_angle.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) target_angle.x += 1;
    const auto state = player_moved(target_angle);
    client_player->set_state(state);
}