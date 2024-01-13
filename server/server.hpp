#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include "client_handler.hpp"

#define SERVER_PORT 8080
#define CLIENT_LIMIT 20
#define CLIENT_TIMEOUT_MILLIS 100000

namespace snek {

    class server {

        std::vector<snek::client_handler> client_sockets;

        std::string handle_request(const std::string& request);

        void start_server(int server_socket);

    public:

        void init();
    };
}

#endif //SNEK_IO_SERVER_HPP
