#ifndef SNEK_IO_SCENE_ERROR_HPP
#define SNEK_IO_SCENE_ERROR_HPP

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "entity.hpp"
#include "scene.hpp"

namespace snek {

    class scene_error : public snek::scene {

        std::shared_ptr<snek::basic_entity<sf::Text>> message_text;
        std::shared_ptr<snek::button> return_button;
        std::function<void()> on_return;

    public:

        scene_error(const std::string& message, const std::function<void()>& on_return);

        bool handle_event(const sf::Event& event) override;

    };
}

#endif //SNEK_IO_SCENE_ERROR_HPP
