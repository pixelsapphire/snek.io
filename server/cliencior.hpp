#ifndef SNEK_IO_CLIENCIOR_HPP
#define SNEK_IO_CLIENCIOR_HPP

#endif //SNEK_IO_CLIENCIOR_HPP

class Client {
public:
    Client(SOCKET socket) : socket(socket), lastActivityTime(time(nullptr)) {}

    SOCKET getSocket() const { return socket; }

    time_t getLastActivityTime() const { return lastActivityTime; }

    void updateActivityTime() { lastActivityTime = time(nullptr); }

    bool operator==(const Client& other) const {
        return this->socket == other.socket;
    }

private:
    SOCKET socket;
    time_t lastActivityTime;
};