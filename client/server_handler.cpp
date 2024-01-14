#include <iostream>
#include "server_handler.hpp"

bool snek::server_handler::connect() {
    const sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    auto status = socket.connect(ip, 8080);
    return status == sf::Socket::Done;
}

void snek::server_handler::disconnect() { socket.disconnect(); }

void snek::server_handler::send_player_position(const sf::Vector2f& position) {
    const std::string request = "c" + std::to_string(position.x) + "x" + std::to_string(position.y) + "y";
    socket.send(request.c_str(), request.size() + 1);
    std::cout << "sent: " << request << " (" << request.size() + 1 << " bytes)" << std::endl;
}

snek::player_state snek::server_handler::fetch_player_state() {
    char buffer[2];
    std::size_t received;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "received: " << buffer << " (" << received << " bytes)" << std::endl;
    return snek::player_state::deserialize(buffer);
}