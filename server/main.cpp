#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>
#include <cstdlib>
#include "cliencior_uni_linu_macc.hpp"
#include <chrono>

#define SERVER_PORT 8080
#define CLIENT_LIMIT 20
#define WAIT4EVENT_MILISEC 1500
#define CLIENT_TIMEOUT_MILISEC 10000

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return -1;
    }

    // Set up the server address structure
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

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

    std::vector<client_uni> client_sockets;

    // Main server loop with poll
    while (true) {
        std::vector<pollfd> poll_fds;

        // Add server socket to the pollfd list
        pollfd server_poll_fd;
        server_poll_fd.fd = server_socket;
        server_poll_fd.events = POLLIN;
        poll_fds.push_back(server_poll_fd);

        // Add client sockets to the pollfd list
        for (const auto& client : client_sockets) {
            pollfd client_poll_fd;
            client_poll_fd.fd = client.get_socket();
            client_poll_fd.events = POLLIN;
            poll_fds.push_back(client_poll_fd);
        }

        // Use poll to wait for events on any of the sockets
        int ready_fds = poll(poll_fds.data(), poll_fds.size(), WAIT4EVENT_MILISEC);
        if (ready_fds < 0) {
            perror("poll");
            break;
        }

        // Check for incoming connections on the server socket
        if (client_sockets.size() < CLIENT_LIMIT && poll_fds[0].revents & POLLIN) {
            sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
            if (client_socket < 0) {
                perror("accept");
                continue;
            }

            // Add the new client socket to the vector
            client_sockets.emplace_back(client_socket);
        }

        // Check for data from clients and handle disconnections
        for (auto it = client_sockets.begin() + 1; it != client_sockets.end(); it++ ) {
            if (poll_fds[it - client_sockets.begin()].revents & POLLIN) {
                char buffer[100];
                ssize_t bytes_received = recv(it->get_socket(), buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    // Handle disconnection or error
                    if (bytes_received == 0) {
                        std::cout << "Client disconnected: " << it->get_socket() << std::endl;
                    } else {
                        perror("recv");
                    }

                    close(it->get_socket());
                    it = client_sockets.erase(it);
                    continue;
                }

                // Handle received data (capitalizing message in this case)
                //it->handle_event(buffer);
                for (int i = 0; i < bytes_received; i++) {
                    buffer[i] = char(toupper(buffer[i]));
                }


                // Send the modified message back to the client
                if (send(it->get_socket(), buffer, bytes_received, 0) < 0) {
                    perror("send");
                    close(it->get_socket());
                    it = client_sockets.erase(it);
                    continue;
                }

                // Update last activity time
                it->update_activity_time();
            }

            if(it->get_time_passed_from_last_activity() > CLIENT_TIMEOUT_MILISEC){
                close(it->get_socket());
                client_sockets.erase(it--);
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