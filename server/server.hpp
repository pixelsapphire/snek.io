#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <cstdio>
#include <functional>
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

        snek::game game_instance;
        snek::config config;
        std::vector<snek::client_handler> client_sockets;
        std::map<std::string, std::function<std::string(snek::client_handler&, std::string)>> requests;

        std::string handle_request(snek::client_handler& client, const std::string& request);

        void start_server(int server_socket);

    public:

        server();

        void init();
    };
}

#endif //SNEK_IO_SERVER_HPP
