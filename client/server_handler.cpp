#include <csignal>
#include <iostream>
#include <set>
#include "server_handler.hpp"
#include "utility.hpp"

snek::server_handler::server_handler() {
    if (not handlers_initialized)
        for (const auto s : snek::factory::range_set<uint8_t>(1, 32) -
                            std::set<uint8_t>{SIGURG, SIGCONT, SIGCHLD, SIGIO, SIGWINCH, SIGINFO})
            std::signal(s, handle_signal);
}

void snek::server_handler::handle_signal(int signal) {
    for (auto s : active_sockets) s->disconnect();
    std::exit(signal);
}

bool snek::server_handler::connect() {
    const sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    auto status = socket.connect(ip, 8080);
    const bool connected = status == sf::Socket::Done;
    if (connected) active_sockets.push_back(&socket);
    return connected;
}

void snek::server_handler::disconnect() {
    const auto socket_position = std::find(active_sockets.begin(), active_sockets.end(), &socket);
    if (socket_position != active_sockets.end()) active_sockets.erase(socket_position);
    socket.disconnect();
}

void snek::server_handler::send_player_position(const sf::Vector2f& position) {
    const std::string request = "c" + std::to_string(position.x) + "x" + std::to_string(position.y) + "y";
    socket.send(request.c_str(), request.size() + 1);
    std::cout << "sent: " << request << " (" << request.size() + 1 << " bytes)" << std::endl;
}

snek::player_state snek::server_handler::fetch_player_state() {
    char buffer[3]{0};
    std::size_t received;
    socket.receive(buffer, sizeof(buffer) - 1, received);
    std::cout << "received: " << buffer << " (" << received << " bytes)" << std::endl;
    return snek::player_state::deserialize(buffer);
}