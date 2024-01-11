#include <iostream>
#include "scene_nickname.hpp"
#include "utility.hpp"

snek::scene_nickname::scene_nickname() : nickname_prompt(snek::make_entity<sf::Text>()),
                                         nickname_view(snek::make_entity<sf::Text>()),
                                         button_text(snek::make_entity<sf::Text>()),
                                         accept_button(snek::make_entity<sf::RectangleShape>(sf::Vector2f(200, 60))) {

    if (not font.loadFromFile("assets/font/jetbrains_mono.ttf"))
        throw std::runtime_error("Failed to load assets");

    auto& prompt = *nickname_prompt;
    prompt->setFont(font);
    prompt->setCharacterSize(24);
    prompt->setFillColor(sf::Color(200, 200, 200));
    prompt->setString("Enter your nickname:");
    prompt->setOrigin(prompt.center());
    prompt.set_position(400, 200);
    add(nickname_prompt);

    auto& view = *nickname_view;
    view->setFont(font);
    view->setCharacterSize(48);
    view->setFillColor(sf::Color::White);
    view->setString("");
    view->setOrigin(view.center());
    view.set_position(400, 280);
    add(nickname_view);

    auto& button = *accept_button;
    button->setFillColor(sf::Color::Transparent);
    button->setOutlineColor(sf::Color::White);
    button->setOutlineThickness(4);
    button->setOrigin(button.center());
    button.set_position(400, 400);
    add(accept_button);

    auto& text = *button_text;
    text->setFont(font);
    text->setCharacterSize(36);
    text->setFillColor(sf::Color::White);
    text->setString("PLAY");
    text->setOrigin(text.center());
    text.set_position(400, 386);
    add(button_text);
}

bool snek::scene_nickname::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 and not nickname.empty()) nickname.pop_back();
        else if (event.text.unicode < 128) nickname += static_cast<char>(event.text.unicode);
        (*nickname_view)->setString(nickname);
        (*nickname_view)->setOrigin(nickname_view->center());
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left and
            (*accept_button)->getGlobalBounds().contains(snek::conv::to_vec2f(event.mouseButton)))
            std::cout << "PLAYING AS " << nickname << std::endl;
    }
    return false;
}