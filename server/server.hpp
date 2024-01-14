#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include "client_handler.hpp"
#include <map>
#include <functional>
#include "game.hpp"


#define SERVER_PORT 8080
#define CLIENT_LIMIT 20
#define CLIENT_TIMEOUT_MILLIS 100000
#define COMMENDS_LENGTH 1

namespace snek {

    class server {

        snek::game game_instance;
        std::vector<snek::client_handler> client_sockets;
        std::map<std::string,std::function<std::string(std::string)>> requests;

        std::string handle_request(const snek::client_handler& client ,const std::string& request);

        void start_server(int server_socket);

    public:

        server ();

        void init();
    };
}

#endif //SNEK_IO_SERVER_HPP
