#ifndef SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP
#define SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP

#include <unistd.h>
#include <netinet/in.h>
#include <chrono>

class client_uni {

    int socket;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_activity_time;

public:

    explicit client_uni(int socket) : socket(socket), last_activity_time(std::chrono::high_resolution_clock::now()) {}

    [[nodiscard]] int get_socket() const { return socket; }

    [[nodiscard]] std::chrono::milliseconds get_time_passed_from_last_activity() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - last_activity_time);
    }

    void update_activity_time() { last_activity_time = std::chrono::high_resolution_clock::now(); }

    bool operator==(const client_uni& other) const {
        return this->socket == other.socket;
    }

    void handle_event(const char buffer[]) {
    }

};

#endif //SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP