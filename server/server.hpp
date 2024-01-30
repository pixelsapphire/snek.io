#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <cstdio>
#include <iostream>
#include <map>
#include <optional>
#include <poll.h>
#include <vector>
#include "client_session.hpp"
#include "config.hpp"
#include "game.hpp"

namespace snek {

    class server {

        int server_socket, ready_events;
        snek::game game_instance;
        snek::config config;
        std::vector<snek::client_session> client_sockets;
        std::map<std::string, std::string (snek::server::*)(snek::client_session&, const std::string&)> requests;
        std::vector<pollfd> poll_events;

        [[nodiscard]] std::string control_request(snek::client_session& client, const std::string& request);

        [[nodiscard]] std::string new_player_request(snek::client_session& client, const std::string& request);

        [[nodiscard]] std::string other_players_request(snek::client_session& client, const std::string& request);

        [[nodiscard]] std::string food_request(snek::client_session& client, const std::string& request);

        [[nodiscard]] std::string process_request(snek::client_session& client, const std::string& request);

        void close_client(std::vector<snek::client_session>::iterator& client);

        [[nodiscard]] std::optional<std::string> receive_data(std::vector<snek::client_session>::iterator& client);

        void send_stored_data(std::vector<snek::client_session>::iterator& client);

        bool handle_client(std::vector<snek::client_session>::iterator& client);

        void event_loop();

    public:

        server();

        void start();
    };
}

#endif //SNEK_IO_SERVER_HPP
