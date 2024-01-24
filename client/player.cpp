#include <utility>
#include "assets.hpp"
#include "player.hpp"

snek::player::player(std::string nickname)
        : nickname(std::move(nickname)),
          nickname_view(this->nickname, snek::assets::get_font(), 16) {
    auto& head = segments.emplace_back(25);
    head.setFillColor(sf::Color::Red);
    head.setOrigin(25, 25);
    nickname_view.setOrigin(nickname_view.getLocalBounds().width / 2, 20);
}

void snek::player::draw(sf::RenderTarget& target) const {
    for (const auto& segment : segments) target.draw(segment);
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
        nickname_view.setString(nickname);
        set_position(state.segments[0].x, state.segments[0].y);
    } else {
        nickname_view.setString(nickname + " (dead)");
        nickname_view.setOrigin(nickname_view.getLocalBounds().width / 2, 20);
    }
}

snek::player::state snek::player::state::parse(const std::string& data) {
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