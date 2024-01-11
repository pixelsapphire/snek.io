#ifndef SNEK_IO_SCENE_HPP
#define SNEK_IO_SCENE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace snek {

    class scene {

        std::vector<std::shared_ptr<snek::entity>> drawables;

    public:

        void update(sf::RenderTarget& target, const sf::Time& delta_time);

        void add(const std::shared_ptr<snek::entity>& drawable);
    };
}

#endif //SNEK_IO_SCENE_HPP
