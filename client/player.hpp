#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace snek {
    class player : public snek::entity {

        std::string nickname;
        sf::CircleShape head;
        sf::Text nickname_view;

    public:

        constexpr inline static float speed = 100;

        explicit player(std::string nickname);

        void draw(sf::RenderTarget& target) const override;

        [[nodiscard]] const sf::Vector2f& get_position() const override;

        void set_position(float x, float y) override;

        enum state {
            alive,
            dead,
            unknown
        };

    };
}

#endif //SNEK_IO_PLAYER_HPP
