#ifndef SNEK_IO_SCENE_HPP
#define SNEK_IO_SCENE_HPP

#include <memory>
#include <queue>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entity.hpp"

namespace snek {

    class scene {

        std::vector<std::shared_ptr<snek::entity>> drawables;
        std::queue<std::shared_ptr<snek::entity>> added_objects, removed_objects;

    public:

        virtual ~scene() = default;

        void step_frame(sf::RenderTarget& target, const sf::Time& delta_time);

        void add(std::shared_ptr<snek::entity> drawable);

        void remove(std::shared_ptr<snek::entity> drawable);

        virtual void update(const sf::Time&) {};

        virtual bool handle_event(const sf::Event&) { return false; };
    };
}

#endif //SNEK_IO_SCENE_HPP
