#include <csignal>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include "server_handler.hpp"
#include "utility.hpp"

snek::server_handler::server_handler() {
    if (not handlers_initialized)
        for (const auto s : std::set<uint8_t>{SIGHUP, SIGINT, SIGTERM, SIGKILL, SIGQUIT, SIGABRT, SIGSEGV, SIGILL,
                                              SIGFPE, SIGBUS, SIGPIPE, SIGSYS, SIGTRAP, SIGXCPU, SIGXFSZ})
            std::signal(s, handle_signal);
}

void snek::server_handler::handle_signal(int signal) {
    for (auto s : active_sockets) s->disconnect();
    std::exit(signal);
}

bool snek::server_handler::connect(const sf::IpAddress& ip, uint16_t port) {
    auto status = socket.connect(ip, port, sf::seconds(2));
    const bool connected = status == sf::Socket::Done;
    if (connected) active_sockets.push_back(&socket);
    return connected;
}

void snek::server_handler::disconnect() {
    const auto socket_position = std::find(active_sockets.begin(), active_sockets.end(), &socket);
    if (socket_position != active_sockets.end()) active_sockets.erase(socket_position);
    socket.disconnect();
}

void snek::server_handler::send(const std::string& data) {
    socket.send((data + '\n').c_str(), data.size() + 1);
    std::cout << "sent: " << data << " (" << data.size() << " bytes)" << std::endl;
}

std::string snek::server_handler::receive() {
    std::stringstream data;
    std::size_t received;
    char read_character = 0;
    while (read_character != '\n' and read_character != '\r') {
        socket.receive(&read_character, 1, received);
        if (received) data << read_character;
    }
    std::string data_string(data.str());
    data_string.resize(data.str().size() - 1);
    std::cout << "received: " << data_string << " (" << data_string.size() << " bytes)" << std::endl;
    return data_string;
}

snek::connection_status snek::server_handler::join(const std::string& nickname) {
    send("n" + nickname);
    const std::string response = receive();
    if (response == "y") return snek::connection_status::connected;
    else if (response == "nf") return snek::connection_status::game_full;
    else if (response == "nt") return snek::connection_status::nickname_taken;
    else return snek::connection_status::error;
}

sf::Vector2f snek::server_handler::get_spawn_point() {
    send("s");
    const std::string response = receive();
    return snek::serial::decode_vector(response.substr(1));
}

snek::player::state snek::server_handler::send_player_velocity(const sf::Vector2f& velocity) {
    send("c" + snek::serial::encode_vector(velocity));
    return snek::player::state::parse(receive());
}

std::map<std::string, sf::Vector2f> snek::server_handler::get_players() {
    send("o");
    const std::string response = receive();
    return snek::serial::decode_players(response.substr(1));
}