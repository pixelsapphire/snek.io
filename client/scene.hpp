#ifndef SNEK_IO_SCENE_HPP
#define SNEK_IO_SCENE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entity.hpp"

namespace snek {

    class scene {

        std::vector<std::shared_ptr<snek::entity>> drawables;

    public:

        virtual ~scene() = default;

        void step_frame(sf::RenderTarget& target, const sf::Time& delta_time);

        virtual void update(const sf::Time& delta_time) {};

        virtual bool handle_event(const sf::Event& event) { return false; };

        void add(std::shared_ptr<snek::entity> drawable);
    };
}

#endif //SNEK_IO_SCENE_HPP
