#include "client_session.hpp"

snek::client_session::client_session(int socket) : socket(socket), is_alive(true), has_message(false),
                                                   last_activity_time(std::chrono::high_resolution_clock::now()) {}

int snek::client_session::get_socket() const { return socket; }

const std::string& snek::client_session::get_nickname() const { return player_nickname; }

void snek::client_session::set_nickname(const std::string& nickname) { this->player_nickname = nickname; }

bool snek::client_session::active() const { return is_alive; }

void snek::client_session::kill() { is_alive = false; }

std::chrono::milliseconds snek::client_session::get_time_passed_from_last_activity() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - last_activity_time);
}

void snek::client_session::update_activity_time() { last_activity_time = std::chrono::high_resolution_clock::now(); }

bool snek::client_session::operator==(const snek::client_session& other) const { return this->socket == other.socket; }

bool snek::client_session::has_message_to_send() const { return has_message; }

void snek::client_session::send_data(std::string data) {
    stored_message = std::move(data);
    has_message = true;
}

const std::string& snek::client_session::get_message() {
    has_message = false;
    return stored_message;
}
