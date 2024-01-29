#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <cstdio>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include "client_handler.hpp"
#include "config.hpp"
#include "game.hpp"

namespace snek {

    class server {

        int server_socket;
        snek::game game_instance;
        snek::config config;
        std::vector<snek::client_handler> client_sockets;
        std::map<std::string, std::string (snek::server::*)(snek::client_handler&, const std::string&)> requests;

        [[nodiscard]] std::string control_request(snek::client_handler& client, const std::string& request);

        [[nodiscard]] std::string new_player_request(snek::client_handler& client, const std::string& request);

        [[nodiscard]] std::string other_players_request(snek::client_handler& client, const std::string& request);

        [[nodiscard]] std::string handle_request(snek::client_handler& client, const std::string& request);

        void close_client(std::vector<snek::client_handler>::iterator& client, std::vector<pollfd>& poll_events);

        bool handle_client(std::vector<snek::client_handler>::iterator& client,
                           std::vector<pollfd>& poll_events, int& ready_events);

        void loop();

    public:

        server();

        void start();
    };
}

#endif //SNEK_IO_SERVER_HPP
