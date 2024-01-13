#include "server.hpp"

std::string snek::server::handle_request(const std::string& request) {
    std::cout << "received data from client" << std::endl;
    std::string response = request;
    std::transform(response.begin(), response.end(), response.begin(), ::toupper);
    return response;
}

void snek::server::start_server(int server_socket) {

    // Main server loop with poll
    while (true) {
        std::vector<pollfd> poll_fds;

        // Add server socket to the pollfd list
        pollfd server_poll_fd{.fd = server_socket, .events = POLLIN};
        poll_fds.push_back(server_poll_fd);

        // Add client_handler sockets to the pollfd list
        for (const auto& client : client_sockets) {
            pollfd client_poll_fd{.fd = client.get_socket(), .events =
            short(client.has_message_to_send() ? POLLIN | POLLOUT : POLLIN)};

            poll_fds.push_back(client_poll_fd);
        }

        // Use poll to wait for events on any of the sockets
        int ready_fds = poll(poll_fds.data(), poll_fds.size(), client_sockets.empty() ? -1 : CLIENT_TIMEOUT_MILLIS);
        if (ready_fds < 0) {
            perror("poll");
            break;
        }

        if (poll_fds[0].revents & POLLIN) ready_fds--;

        const auto close_client = [&](auto& it) {
            close(it->get_socket());
            poll_fds.erase(poll_fds.begin() + (it - client_sockets.begin() + 1));
            client_sockets.erase(it--);
        };

        // Obsługa zdarzeń (bez serwera - dodawania klientow)
        for (auto client = client_sockets.begin(); ready_fds > 0 and client != client_sockets.end(); ++client) {
            bool ready_fds_decrement = true;

            // Obsługa zdarzeń POLLIN
            if (poll_fds[client - client_sockets.begin() + 1].revents & POLLIN) {
                ready_fds_decrement = false;
                ready_fds--;
                char buffer[100]{0};
                ssize_t bytes_received = recv(client->get_socket(), buffer, sizeof(buffer) - 1, 0);
                if (bytes_received <= 0) {
                    if (bytes_received == 0) {
                        std::cout << "Client disconnected: " << client->get_socket() << std::endl;
                    } else {
                        perror("recv");
                    }

                    close_client(client);
                    continue;
                }

                //Handle received data
                client->send_data(handle_request(buffer));
                client->update_activity_time();
            }

            // Obsługa zdarzeń POLLOUT
            if (client->has_message_to_send() and poll_fds[client - client_sockets.begin() + 1].revents & POLLOUT) {
                if (ready_fds_decrement) ready_fds--;

                // Obsługa zdarzeń POLLOUT dla danego klienta
                const std::string& message = client->get_message();
                ssize_t bytes_sent = send(client->get_socket(), message.c_str(), message.size(), 0);

                if (bytes_sent > 0) {
                    // Wiadomość została wysłana poprawnie
                    std::cout << "Wysłano wiadomość do klienta: " << client->get_socket() << std::endl;
                } else if (bytes_sent == 0) {
                    // Połączenie zostało zamknięte przez klienta
                    std::cout << "Połączenie zostało zamknięte przez klienta: " << client->get_socket() << std::endl;
                    close_client(client);
                } else {
                    // Błąd podczas wysyłania
                    perror("send");
                    close_client(client);
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
                // Add the new client_handler socket to the vector
                std::cout << "new client_handler added" << std::endl;
                client_sockets.emplace_back(client_socket);
            }
        }

        for (auto it = client_sockets.begin(); it != client_sockets.end(); ++it) {
            if (it->get_time_passed_from_last_activity().count() > CLIENT_TIMEOUT_MILLIS) {
                close(it->get_socket());
                client_sockets.erase(it--);
                std::cout << " Client timeout yeet! " << std::endl;
            }
        }

    }

    // Close client_handler sockets
    for (const auto& client : client_sockets) {
        close(client.get_socket());
    }
}

void snek::server::init() {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        std::exit(-1);
    }

    // Set up the server address structure
    sockaddr_in server_addr{.sin_family = AF_INET, .sin_port = htons(SERVER_PORT), .sin_addr={.s_addr = INADDR_ANY}};

    // Bind the server socket to the specified address
    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        std::exit(-1);
    }

    // Listen for incoming connections
    if (listen(server_socket, CLIENT_LIMIT) < 0) {
        perror("listen");
        close(server_socket);
        std::exit(-1);
    }

    // Start the server
    start_server(server_socket);

    // Close the server socket
    close(server_socket);
}