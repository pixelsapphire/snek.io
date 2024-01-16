#include <iostream>
#include "assets.hpp"
#include "scene_nickname.hpp"
#include "utility.hpp"

snek::scene_nickname::scene_nickname(std::function<void(const std::string&)> on_nickname_selected)
        : on_nickname_selected(std::move(on_nickname_selected)),
          nickname_prompt(snek::make_entity<sf::Text>()),
          nickname_view(snek::make_entity<sf::Text>()),
          accept_button(std::make_shared<snek::button>("PLAY")) {

    auto& prompt = *nickname_prompt;
    prompt->setFont(snek::assets::get_font());
    prompt->setCharacterSize(24);
    prompt->setFillColor(sf::Color(200, 200, 200));
    prompt->setString("Enter your nickname:");
    prompt->setOrigin(prompt.center());
    prompt.set_position(400, 200);
    add(nickname_prompt);

    auto& view = *nickname_view;
    view->setFont(snek::assets::get_font());
    view->setCharacterSize(48);
    view->setFillColor(sf::Color::White);
    view->setString("");
    view->setOrigin(view.center());
    view.set_position(400, 280);
    add(nickname_view);

    auto& button = *accept_button;
    button.set_position(400, 400);
    add(accept_button);
}

bool snek::scene_nickname::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 and not nickname.empty()) nickname.pop_back();
        else if (event.text.unicode > 32 and event.text.unicode <= 126) nickname += char(event.text.unicode);
        (*nickname_view)->setString(nickname);
        (*nickname_view)->setOrigin(nickname_view->center().x, 24);
    } else if ((accept_button->clicked(event) or snek::event::key_pressed(event, sf::Keyboard::Enter))
               and not nickname.empty())
        on_nickname_selected(nickname);

    return false;
}