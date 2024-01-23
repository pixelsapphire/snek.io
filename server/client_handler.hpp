#ifndef SNEK_IO_CLIENT_HPP
#define SNEK_IO_CLIENT_HPP

#include <algorithm>
#include <chrono>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

namespace snek {

    class client_handler {

        int socket;
        std::string player_nickname;
        bool has_message;
        std::chrono::time_point<std::chrono::high_resolution_clock> last_activity_time;
        std::string stored_message;

    public:

        explicit client_handler(int socket) : socket(socket), has_message(false),
                                              last_activity_time(std::chrono::high_resolution_clock::now()) {}

        [[nodiscard]] int get_socket() const { return socket; }

        [[nodiscard]] const std::string& get_nickname() const { return player_nickname; }

        void set_nickname(const std::string& nickname) { this->player_nickname = nickname; }

        [[nodiscard]] std::chrono::milliseconds get_time_passed_from_last_activity() const {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - last_activity_time);
        }

        void update_activity_time() { last_activity_time = std::chrono::high_resolution_clock::now(); }

        bool operator==(const client_handler& other) const { return this->socket == other.socket; }

        [[nodiscard]] bool has_message_to_send() const { return has_message; }

        void send_data(std::string data) {
            stored_message = std::move(data);
            has_message = true;
        }

        const std::string& get_message() {
            has_message = false;
            return stored_message;
        }

    };
}

#endif //SNEK_IO_CLIENT_HPP