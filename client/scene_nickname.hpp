#ifndef SNEK_IO_SCENE_NICKNAME_HPP
#define SNEK_IO_SCENE_NICKNAME_HPP

#include <functional>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "scene.hpp"

namespace snek {

    class scene_nickname : public snek::scene {

        std::function<void(const std::string&)> on_nickname_selected;
        std::string nickname;
        std::shared_ptr<snek::basic_entity<sf::Text>> nickname_prompt, nickname_view, button_text;
        std::shared_ptr<snek::basic_entity<sf::RectangleShape>> accept_button;

    public:

        scene_nickname(std::function<void(const std::string&)> on_nickname_selected);

        bool handle_event(const sf::Event& event) override;
    };

}

#endif //SNEK_IO_SCENE_NICKNAME_HPP
