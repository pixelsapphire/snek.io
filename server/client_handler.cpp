#include "client_handler.hpp"

snek::client_handler::client_handler(int socket) : socket(socket), has_message(false),
                                                   last_activity_time(std::chrono::high_resolution_clock::now()) {}

int snek::client_handler::get_socket() const { return socket; }

const std::string& snek::client_handler::get_nickname() const { return player_nickname; }

void snek::client_handler::set_nickname(const std::string& nickname) { this->player_nickname = nickname; }

std::chrono::milliseconds snek::client_handler::get_time_passed_from_last_activity() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - last_activity_time);
}

void snek::client_handler::update_activity_time() { last_activity_time = std::chrono::high_resolution_clock::now(); }

bool snek::client_handler::operator==(const snek::client_handler& other) const { return this->socket == other.socket; }

bool snek::client_handler::has_message_to_send() const { return has_message; }

void snek::client_handler::send_data(std::string data) {
    stored_message = std::move(data);
    has_message = true;
}

const std::string& snek::client_handler::get_message() {
    has_message = false;
    return stored_message;
}
