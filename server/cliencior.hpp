//
// Created by stas on 11.01.2024.
//

#ifndef SNEK_IO_CLIENCIOR_HPP
#define SNEK_IO_CLIENCIOR_HPP

#endif //SNEK_IO_CLIENCIOR_HPP

class Client {
public:
    Client(SOCKET socket) : socket(socket), lastActivityTime(time(nullptr)) {}

    SOCKET getSocket() const { return socket; }
    time_t getLastActivityTime() const { return lastActivityTime; }
    void updateActivityTime() { lastActivityTime = time(nullptr); }

private:
    SOCKET socket;
    time_t lastActivityTime;
};