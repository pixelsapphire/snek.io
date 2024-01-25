#include <utility>
#include "assets.hpp"
#include "player.hpp"
#include <sstream>

snek::player::player(std::string nickname)
        : nickname(std::move(nickname)),
          nickname_view(this->nickname, snek::assets::get_font(), 16) {
    auto& head = segments.emplace_back(25);
    head.setFillColor(sf::Color::Red);
    head.setOrigin(25, 25);
    nickname_view.setOrigin(nickname_view.getLocalBounds().width / 2, 20);
}

void snek::player::draw(sf::RenderTarget& target) const {
    for (const auto& segment : segments) {
        auto* s = &segment;
        target.draw(*s);
    }
    target.draw(nickname_view);
}

const sf::Vector2f& snek::player::get_position() const {
    return segments[0].getPosition();
}

void snek::player::set_position(float x, float y) {
    segments[0].setPosition(x, y);
    nickname_view.setPosition(x, y - 25);
}

void snek::player::set_state(const snek::player::state& state) {
    if (state.alive) {
        set_position(state.segments[0].x, state.segments[0].y);
        segments.resize(state.segments.size(), segments[0]);
        for (size_t i = 1; i < state.segments.size(); ++i)
            segments[i].setPosition(state.segments[i].x, state.segments[i].y);
    } else {
        nickname_view.setString(nickname + " (dead)");
        nickname_view.setOrigin(nickname_view.getLocalBounds().width / 2, 20);
    }
}

snek::player::state snek::player::state::parse_client(const std::string& data) {
    state state{.alive = data[0] == 'a'};
    if (state.alive) {
        std::string_view view(data);
        view.remove_prefix(1);
        while (not view.empty()) {
            float x = std::stof(std::string(view.substr(0, view.find('x'))));
            view.remove_prefix(view.find('x') + 1);
            float y = std::stof(std::string(view.substr(0, view.find('y'))));
            view.remove_prefix(view.find('y') + 1);
            state.segments.emplace_back(x, y);
        }
    }
    return state;
}

std::map<std::string, snek::player::state> snek::player::state::parse_others(const std::string& data) {

    std::map<std::string, snek::player::state> players;
    std::stringstream ss(data);
    std::string n;
    std::getline(ss, n, 'n');
    size_t number_of_players = std::stoul(n);

    for (size_t i = 0; i < number_of_players; ++i) {

        std::string nickname, x, y, s;
        std::getline(ss, nickname, ' ');
        std::getline(ss, s, 's');
        size_t number_of_segments = std::stoul(s);
        player::state player;
        
        for (size_t j = 0; j < number_of_segments; ++j) {
            std::getline(ss, x, 'x'), std::getline(ss, y, 'y');
            players[nickname].segments.emplace_back(std::stof(x), std::stof(y));
        }
    }
    return players;
}