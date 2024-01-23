#include "server.hpp"
#include <sstream>

snek::server::server() : config("config/s_config.txt") {
    //c - check if dead
    requests["c"] = [&](const snek::client_handler& client, const std::string& command_body) {
        const std::string& nickname = client.get_nickname();
        const auto x_pos = command_body.find('x'), y_pos = command_body.find('y');
        const auto x = std::stof(command_body.substr(0, x_pos)),
                y = std::stof(command_body.substr(x_pos + 1, y_pos - x_pos - 1));
        game_instance.store_player_position(nickname, x, y);

        return game_instance.is_alive(nickname) ? "a" : "d";
    };

    //n - new player
    requests["n"] = [&](const snek::client_handler&, const std::string& command_body) {
        if (game_instance.player_count() > MAX_PLAYERS)
            return "nf"; //not connected - full

        const std::string& nickname = command_body;//client.get_nickname();
        if (game_instance.nickname_taken(nickname))
            return "nt"; // nickname taken

        game_instance.add_player(nickname);
        return "y"; //game_instance.get_player_position (nickname);
    };

    //s - spawn
    requests["s"] = [&](const snek::client_handler& client, const std::string&) {
        const std::string& nickname = client.get_nickname();
        return "l" + game_instance.get_player_position(nickname);
    };

    //o - other players
    requests["o"] = [&](const snek::client_handler& client, const std::string&) {
        const std::string& nickname = client.get_nickname();
        std::stringstream ss;
        ss << "p" << game_instance.player_count() - 1 << "n";
        for (const auto& player : game_instance.get_players()) {
            if (player.first == nickname)
                continue;
            ss << player.first << " " << game_instance.get_player_position(player.first);
        }
        return ss.str();
    };
}

std::string snek::server::handle_request(const snek::client_handler& client, const std::string& request) {
    std::cout << "received data from client " << client.get_socket() << ": " << request
              << " (" << request.size() << ") bytes" << std::endl;
    const std::string command = request.substr(0, COMMAND_LENGTH),
            arguments = request.substr(COMMAND_LENGTH, request.size() - COMMAND_LENGTH - 1);
    if (requests.contains(command)) return requests[command](client, arguments) + "\n";
    return "e\n";
}

void snek::server::start_server(int server_socket) {

    // Main server loop with poll
    while (true) {
        std::vector<pollfd> poll_fds;

        // Add server socket to the pollfd list
        pollfd server_poll_fd{.fd = server_socket, .events = POLLIN, .revents = 0};
        poll_fds.push_back(server_poll_fd);

        // Add client_handler sockets to the pollfd list
        for (const auto& client : client_sockets) {
            pollfd client_poll_fd{.fd = client.get_socket(), .events =
            short(client.has_message_to_send() ? POLLIN | POLLOUT : POLLIN), .revents = 0};

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
                ssize_t bytes_received = recv(client->get_socket(), buffer, sizeof(buffer) - 1, 0); //MSG_DONTWAIT
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
                const std::string response = handle_request(*client, buffer);
                std::cout << "Sending response to client " << client->get_socket() << ": " << response
                          << " (" << response.size() << ") bytes" << std::endl;
                client->send_data(response);
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
    sockaddr_in server_addr{.sin_len = sizeof(server_addr), .sin_family = AF_INET,
            .sin_port = htons(config.get_int("port")), .sin_addr = {.s_addr = INADDR_ANY}, .sin_zero = {0}};

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