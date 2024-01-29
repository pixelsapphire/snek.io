#ifndef SNEK_IO_PLAYER_HPP
#define SNEK_IO_PLAYER_HPP

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace snek {

    class player : public snek::entity {

        std::string nickname;
        std::vector<sf::CircleShape> segments;
        sf::Text nickname_view;

    public:

        explicit player(std::string nickname);

        void draw(sf::RenderTarget& target) const override;

        [[nodiscard]] const sf::Vector2f& get_position() const override;

        void set_position(float x, float y) override;

        struct state {

            bool alive = false;
            std::vector<sf::Vector2f> segments;

            [[nodiscard]] static state parse_client(const std::string& data);

            [[nodiscard]] static std::map<std::string, state> parse_others(const std::string& data);
        };

        void set_state(const state& state);

    };
}

#endif //SNEK_IO_PLAYER_HPP
