#ifndef SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP
#define SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP

#include <unistd.h>
#include <netinet/in.h>
#include <chrono>
#include <string>

class client_uni {

    int socket;
    bool hasMessage;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_activity_time;
    std::string message;

public:

    explicit client_uni(int socket) : socket(socket), hasMessage(false), last_activity_time(std::chrono::high_resolution_clock::now()) {}

    [[nodiscard]] int getSocket() const { return socket; }

    [[nodiscard]] std::chrono::milliseconds get_time_passed_from_last_activity() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - last_activity_time);
    }

    void update_activity_time() { last_activity_time = std::chrono::high_resolution_clock::now(); }

    bool operator==(const client_uni& other) const {
        return this->socket == other.socket;
    }

    [[nodiscard]] bool hasMessageToSend() const {
        return hasMessage;
    }

    void recieveData(const char buffer[]) {
        message = std::string (buffer);
        std::transform(message.begin(), message.end(), message.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        this->hasMessage = true;
    }

    std::string getMessage() {
        hasMessage = false;
        return message;
    }

};

#endif //SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP