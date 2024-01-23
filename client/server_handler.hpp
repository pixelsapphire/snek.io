#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <map>
#include <optional>
#include <vector>
#include <SFML/Network.hpp>
#include "player.hpp"

namespace snek {

    enum connection_status {
        connected, game_full, nickname_taken, error
    };

    class server_handler {

        sf::TcpSocket socket;

        static inline bool handlers_initialized = false;
        static inline std::vector<sf::TcpSocket*> active_sockets;

        static void handle_signal(int);

    public:

        server_handler();

        bool connect();

        void disconnect();

        void send(const std::string& data);

        [[nodiscard]] std::string receive(size_t buffer_size = 32);

        [[nodiscard]] snek::connection_status join(const std::string& nickname);

        [[nodiscard]] sf::Vector2f get_spawn_point();

        [[nodiscard]] snek::player::state send_player_position(const sf::Vector2f& position);

        [[nodiscard]] std::map<std::string, sf::Vector2f> get_players();
    };
}

#endif //SNEK_IO_SERVER_HPP
