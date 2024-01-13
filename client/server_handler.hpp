#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#include <SFML/Network.hpp>

namespace snek {

    class server_handler {

        sf::TcpSocket socket;

    public:

        bool connect();

        void disconnect();
    };
}

#endif //SNEK_IO_SERVER_HPP
