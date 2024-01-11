#include "scene.hpp"

void snek::scene::update(sf::RenderTarget& target, const sf::Time& delta_time) {
    for (auto& drawable : drawables) drawable->update(delta_time);
    for (auto& drawable : drawables) drawable->draw(target);
}

void snek::scene::add(const std::shared_ptr<snek::entity>& drawable) {
    drawables.push_back(drawable);
}