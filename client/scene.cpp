#include "scene.hpp"

void snek::scene::step_frame(sf::RenderTarget& target, const sf::Time& delta_time) {
    update(delta_time);
    for (auto& drawable : drawables) drawable->update(delta_time);
    for (auto& drawable : drawables) drawable->draw(target);
}

void snek::scene::update(const sf::Time& delta_time) {
    while (not added_objects.empty()) {
        drawables.push_back(added_objects.front());
        added_objects.pop();
    }
    while (not removed_objects.empty()) {
        drawables.erase(std::remove(drawables.begin(), drawables.end(), removed_objects.front()), drawables.end());
        removed_objects.pop();
    }
}

void snek::scene::add(std::shared_ptr<snek::entity> drawable) {
    added_objects.push(std::move(drawable));
}

void snek::scene::remove(std::shared_ptr<snek::entity> drawable) {
    removed_objects.push(std::move(drawable));
}