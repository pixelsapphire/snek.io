#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include "client.hpp"

#define SERVER_PORT 8080
#define CLIENT_LIMIT 20
#define CLIENT_TIMEOUT_MILISEC 100000

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return -1;
    }

    // Set up the server address structure
    sockaddr_in server_addr{.sin_family = AF_INET, .sin_port = htons(SERVER_PORT), .sin_addr={.s_addr = INADDR_ANY}};

    // Bind the server socket to the specified address
    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_socket, CLIENT_LIMIT) < 0) {
        perror("listen");
        close(server_socket);
        return -1;
    }

    std::vector<snek::client> client_sockets;

    // Main server loop with poll
    while (true) {
        std::vector<pollfd> poll_fds;

        // Add server socket to the pollfd list
        pollfd server_poll_fd{.fd = server_socket, .events = POLLIN};
        poll_fds.push_back(server_poll_fd);

        // Add client sockets to the pollfd list
        for (const auto& client : client_sockets) {
            pollfd client_poll_fd{.fd = client.get_socket(), .events =
            short(client.has_message_to_send() ? POLLIN | POLLOUT : POLLIN)};

            poll_fds.push_back(client_poll_fd);
        }

        // Use poll to wait for events on any of the sockets
        int ready_fds = poll(poll_fds.data(), poll_fds.size(), client_sockets.empty() ? -1 : CLIENT_TIMEOUT_MILISEC);
        if (ready_fds < 0) {
            perror("poll");
            break;
        }

        if (poll_fds[0].revents & POLLIN) ready_fds--;

        const auto close_client = [&](auto it) {
            close(it->get_socket());
            poll_fds.erase(poll_fds.begin() + (it - client_sockets.begin() + 1));
            client_sockets.erase(it--);
        };

        // Obsługa zdarzeń (bez serwera - dodawania klientow)
        for (auto it = client_sockets.begin(); ready_fds > 0 and it != client_sockets.end(); ++it) {
            bool ready_fds_decrement = true;

            // Obsługa zdarzeń POLLIN
            if (poll_fds[it - client_sockets.begin() + 1].revents & POLLIN) {
                ready_fds_decrement = false;
                ready_fds--;
                char buffer[100]{0};
                ssize_t bytes_received = recv(it->get_socket(), buffer, sizeof(buffer) - 1, 0);
                if (bytes_received <= 0) {
                    if (bytes_received == 0) {
                        std::cout << "Client disconnected: " << it->get_socket() << std::endl;
                    } else {
                        perror("recv");
                    }

                    close_client(it);
                    continue;
                }

                std::cout << "recieved data from client " << std::endl;
                //Handle recieved data
                it->receive_data(buffer);
                it->update_activity_time();
            }

            // Obsługa zdarzeń POLLOUT
            if (it->has_message_to_send() and poll_fds[it - client_sockets.begin() + 1].revents & POLLOUT) {
                if (ready_fds_decrement) ready_fds--;

                // Obsługa zdarzeń POLLOUT dla danego klienta
                const std::string& message = it->get_message();
                ssize_t bytes_sent = send(it->get_socket(), message.c_str(), message.size(), 0);

                if (bytes_sent > 0) {
                    // Wiadomość została wysłana poprawnie
                    std::cout << "Wysłano wiadomość do klienta: " << it->get_socket() << std::endl;
                } else if (bytes_sent == 0) {
                    // Połączenie zostało zamknięte przez klienta
                    std::cout << "Połączenie zostało zamknięte przez klienta: " << it->get_socket() << std::endl;
                    close_client(it);
                } else {
                    // Błąd podczas wysyłania
                    perror("send");
                    close_client(it);
                }
            }
        }

        // Check for incoming connections on the server socket
        if (client_sockets.size() < CLIENT_LIMIT and poll_fds[0].revents & POLLIN) {
            sockaddr_in client_addr{};
            socklen_t client_addr_len = sizeof(client_addr);
            int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
            if (client_socket < 0) {
                perror("accept");
                //continue;
            } else {
                // Add the new client socket to the vector
                std::cout << "new client added" << std::endl;
                client_sockets.emplace_back(client_socket);
            }
        }

        for (auto it = client_sockets.begin(); it != client_sockets.end(); ++it) {
            if (it->get_time_passed_from_last_activity().count() > CLIENT_TIMEOUT_MILISEC) {
                close(it->get_socket());
                client_sockets.erase(it--);
                std::cout << " Client timeout yeet! " << std::endl;
            }
        }

    }

    // Close client sockets
    for (const auto& client : client_sockets) {
        close(client.get_socket());
    }

    // Close the server socket
    close(server_socket);

    return 0;
}