//
// Created by stas on 11.01.2024.
//

#ifndef SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP
#define SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP

#endif //SNEK_IO_CLIENCIOR_UNI_LINU_MACC_HPP
#include <unistd.h>
#include <netinet/in.h>
#include <chrono>

class client_uni {
public:
    explicit client_uni(int socket) : socket(socket), lastActivityTime(std::chrono::high_resolution_clock::now()) {}

    [[nodiscard]] int getSocket() const { return socket; }

    [[nodiscard]] long long getTimePassedFromLastActivity() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - lastActivityTime).count();; }

    void updateActivityTime() { lastActivityTime = time(nullptr); }

    bool operator==(const client_uni& other) const {
        return this->socket == other.socket;
    }

    void handleEvent(const char buffer []) {

    }

private:
    int socket;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastActivityTime;
};