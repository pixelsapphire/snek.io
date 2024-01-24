#ifndef SNEK_IO_CLIENT_HPP
#define SNEK_IO_CLIENT_HPP

#include <chrono>
#include <string>

namespace snek {

    class client_handler {

        int socket;
        std::string player_nickname;
        bool has_message;
        std::chrono::time_point<std::chrono::high_resolution_clock> last_activity_time;
        std::string stored_message;

    public:

        explicit client_handler(int socket);

        [[nodiscard]] int get_socket() const;

        [[nodiscard]] const std::string& get_nickname() const;

        void set_nickname(const std::string& nickname);

        [[nodiscard]] std::chrono::milliseconds get_time_passed_from_last_activity() const;

        void update_activity_time();

        bool operator==(const client_handler& other) const;

        [[nodiscard]] bool has_message_to_send() const;

        void send_data(std::string data);

        [[nodiscard]] const std::string& get_message();

    };
}

#endif //SNEK_IO_CLIENT_HPP