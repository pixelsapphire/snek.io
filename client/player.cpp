#include <utility>
#include "assets.hpp"
#include "player.hpp"

snek::player::player(std::string nickname)
        : nickname(std::move(nickname)),
          head(25),
          nickname_view(this->nickname, snek::assets::get_font(), 16) {
    head.setFillColor(sf::Color::Red);
    head.setOrigin(25, 25);
    nickname_view.setOrigin(nickname_view.getLocalBounds().width / 2, 20);
}

void snek::player::draw(sf::RenderTarget& target) const {
    target.draw(head);
    target.draw(nickname_view);
}

const sf::Vector2f& snek::player::get_position() const {
    return head.getPosition();
}

void snek::player::set_position(float x, float y) {
    head.setPosition(x, y);
    nickname_view.setPosition(x, y - 25);
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