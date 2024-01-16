#include "assets.hpp"
#include "scene_error.hpp"

snek::scene_error::scene_error(const std::string& message, const std::function<void()>& on_return)
        : message_text(std::make_shared<snek::basic_entity<sf::Text>>()),
          return_button(std::make_shared<snek::button>("RETURN")),
          on_return(on_return) {

    auto& text = *message_text;
    text->setFont(snek::assets::get_font());
    text->setCharacterSize(30);
    text->setFillColor(sf::Color::White);
    text->setString(message);
    text->setOrigin(text.center());
    text.set_position(400, 250);
    add(message_text);

    return_button->set_position(400, 400);
    add(return_button);
}

bool snek::scene_error::handle_event(const sf::Event& event) {
    if (not return_button->clicked(event)) return false;
    on_return();
    return true;
}

