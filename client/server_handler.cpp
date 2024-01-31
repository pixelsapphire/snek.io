#include <csignal>
#include <iostream>
#include <set>
#include <sstream>
#include "common_utility.hpp"
#include "server_handler.hpp"
#include "utility.hpp"

snek::connection_status snek::connection_status::connected(0), snek::connection_status::game_full(1),
        snek::connection_status::nickname_taken(2), snek::connection_status::error(3);

snek::connection_status::connection_status(uint8_t status_id) : status_id(status_id) {}

bool snek::connection_status::operator==(const snek::connection_status& other) const { return status_id == other.status_id; }

sf::Vector2f snek::connection_status::get_initial_position() const { return initial_position; }

snek::connection_status snek::connection_status::spawned_at(const sf::Vector2f& position) {
    connection_status status(0);
    status.initial_position = position;
    return status;
}

snek::server_handler::server_handler() {
    if (not handlers_initialized)
        for (const auto s : std::set<uint8_t>{SIGHUP, SIGINT, SIGTERM, SIGKILL, SIGQUIT, SIGABRT, SIGSEGV, SIGILL,
                                              SIGFPE, SIGBUS, SIGPIPE, SIGSYS, SIGTRAP, SIGXCPU, SIGXFSZ})
            std::signal(s, handle_signal);
}

void snek::server_handler::handle_signal(int signal) {
    if (active_socket != nullptr) active_socket->disconnect();
    std::exit(signal);
}

bool snek::server_handler::connect(const sf::IpAddress& ip, uint16_t port) {
    if (active_socket != nullptr) active_socket->disconnect();
    const bool connected = socket.connect(ip, port, sf::seconds(2)) == sf::Socket::Done;
    if (connected) active_socket = &socket;
    return connected;
}

void snek::server_handler::disconnect() {
    socket.disconnect();
    active_socket = nullptr;
}

void snek::server_handler::send(const std::string& data) {
    socket.send((data + '\n').c_str(), data.size() + 1);
#ifdef SNEK_DEBUG
    std::cout << "sent: " << data << " (" << data.size() << " bytes)" << std::endl;
#endif
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
#ifdef SNEK_DEBUG
    std::cout << "received: " << data_string << " (" << data_string.size() << " bytes)" << std::endl;
#endif
    return data_string;
}

snek::connection_status snek::server_handler::join(const std::string& nickname) {
    send("n" + nickname);
    const std::string response = receive();
    if (response.starts_with("y")) return snek::connection_status::spawned_at(snek::serial::decode_vector(response.substr(1)));
    else if (response == "nf") return snek::connection_status::game_full;
    else if (response == "nt") return snek::connection_status::nickname_taken;
    else return snek::connection_status::error;
}

snek::player::state snek::server_handler::send_player_velocity(const sf::Vector2i& velocity) {
    send(snek::concat("c", snek::serial::encode_vector(velocity)));
    return snek::player::state::parse_client(receive());
}

std::map<std::string, snek::player::state> snek::server_handler::get_players() {
    send("o");
    return player::state::parse_others(receive());
}

std::vector<sf::Vector2f> snek::server_handler::get_food() {
    send("f");
    return snek::serial::decode_vector_array(receive().substr(1));
}
