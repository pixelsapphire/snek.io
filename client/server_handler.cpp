#include "server_handler.hpp"

bool snek::server_handler::connect() {
    const sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    auto status = socket.connect(ip, 8080);
    return status == sf::Socket::Done;
}

void snek::server_handler::disconnect() { socket.disconnect(); }