#ifndef SNEK_IO_CLIENT_HPP
#define SNEK_IO_CLIENT_HPP

#include <algorithm>
#include <chrono>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

namespace snek {

    class client {

        int socket;
        bool has_message;
        std::chrono::time_point<std::chrono::high_resolution_clock> last_activity_time;
        std::string stored_message;

    public:

        explicit client(int socket) : socket(socket), has_message(false),
                                      last_activity_time(std::chrono::high_resolution_clock::now()) {}

        [[nodiscard]] int get_socket() const { return socket; }

        [[nodiscard]] std::chrono::milliseconds get_time_passed_from_last_activity() const {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - last_activity_time);
        }

        void update_activity_time() { last_activity_time = std::chrono::high_resolution_clock::now(); }

        bool operator==(const client& other) const { return this->socket == other.socket; }

        [[nodiscard]] bool has_message_to_send() const { return has_message; }

        void receive_data(const char* buffer) {
            stored_message = std::string(buffer);
            std::transform(stored_message.begin(), stored_message.end(), stored_message.begin(),
                           [](char c) { return std::toupper(c); });
            has_message = true;
        }

        const std::string& get_message() {
            has_message = false;
            return stored_message;
        }

    };
}

#endif //SNEK_IO_CLIENT_HPP