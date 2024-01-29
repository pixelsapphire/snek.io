#include "scene_main.hpp"
#include "utility.hpp"

snek::scene_main::scene_main(const std::function<snek::player::state(const sf::Vector2f& position)>& on_player_movement,
                             const std::function<std::map<std::string, snek::player::state>()>& players_provider,
                             const std::function<std::vector<sf::Vector2f>()>& food_provider)
        : player_moved(on_player_movement), fetch_players(players_provider), fetch_food(food_provider) {}

void snek::scene_main::spawn_player(const std::string& nickname, bool client, const sf::Vector2f& client_position) {
    auto player = std::make_shared<snek::player>(nickname);
    add(player);
    if (client) {
        client_player = player;
        player->set_position(client_position);
    }
    else other_players[nickname] = player;
}

void snek::scene_main::remove_player(const std::string& nickname) {
    remove(other_players[nickname]);
}

void snek::scene_main::update(const sf::Time& delta_time) {
    snek::scene::update(delta_time);
    sf::Vector2f target_angle;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) target_angle.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) target_angle.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) target_angle.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) target_angle.x += 1;
    const auto player_state = player_moved(target_angle);
    client_player->set_state(player_state);
    if (player_state.alive) {
        update_food();
        update_players();
    }
}

void snek::scene_main::update_food() {
    const auto food = fetch_food();
    if (food.size() < food_units.size()) {
        const size_t removed_food = food_units.size() - food.size();
        for (size_t i = 0; i < removed_food; ++i) {
            remove(food_units.back());
            food_units.pop_back();
        }
    }
    else if (food.size() > food_units.size()) {
        const size_t new_food = food.size() - food_units.size();
        for (size_t i = 0; i < new_food; ++i) {
            auto food_unit = snek::make_entity<sf::CircleShape>(5);
            (*food_unit)->setFillColor(sf::Color::Green);
            (*food_unit)->setOrigin(10, 10);
            food_units.push_back(food_unit);
            add(food_unit);
        }
    }
    for (size_t i = 0; i < food.size(); ++i) food_units[i]->set_position(food[i]);
}

void snek::scene_main::update_players() {
    const auto players = fetch_players();
    for (auto it = other_players.begin(); it != other_players.end();) {
        if (players.contains(it->first)) ++it;
        else {
            remove_player(it->first);
            it = other_players.erase(it);
        }
    }
    for (const auto& [nickname, state] : players) {
        if (not other_players.contains(nickname)) spawn_player(nickname, false);
        other_players.at(nickname)->set_state(state);
    }
}