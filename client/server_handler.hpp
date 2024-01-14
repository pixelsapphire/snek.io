#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <SFML/Network.hpp>
#include "player.hpp"

namespace snek {

    class server_handler {

        sf::TcpSocket socket;

    public:

        bool connect();

        void disconnect();

        void send_player_position(const sf::Vector2f& position);

        [[nodiscard]] snek::player_state fetch_player_state();
    };
}

#endif //SNEK_IO_SERVER_HPP
