#include <SFML/Window.hpp>
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