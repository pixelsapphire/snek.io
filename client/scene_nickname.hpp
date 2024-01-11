#ifndef SNEK_IO_SCENE_NICKNAME_HPP
#define SNEK_IO_SCENE_NICKNAME_HPP

#include <memory>
#include "entity.hpp"
#include "scene.hpp"

namespace snek {

    class scene_nickname : public snek::scene {

        std::string nickname;
        sf::Font font;
        std::shared_ptr<snek::basic_entity<sf::Text>> nickname_prompt, nickname_view, button_text;
        std::shared_ptr<snek::basic_entity<sf::RectangleShape>> accept_button;

    public:

        scene_nickname();

        bool handle_event(const sf::Event& event) override;
    };

}

#endif //SNEK_IO_SCENE_NICKNAME_HPP
