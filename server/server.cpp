#include <sstream>
#include "server.hpp"
#include "utility.hpp"

#define COMMAND_LENGTH 1

snek::server::server() : server_socket(-1), config(snek::config::path() + "/s_config.txt") {
    requests["c"] = &snek::server::control_request;
    requests["n"] = &snek::server::new_player_request;
    requests["o"] = &snek::server::other_players_request;
    requests["f"] = &snek::server::food_request;
}

std::string snek::server::control_request(snek::client_handler& client, const std::string& request) {
    const std::string& nickname = client.get_nickname();
    const auto x_pos = request.find('x'), y_pos = request.find('y');
    const auto x = std::stof(request.substr(0, x_pos)),
            y = std::stof(request.substr(x_pos + 1, y_pos - x_pos - 1));

    const auto time = float(client.get_time_passed_from_last_activity().count()) / 1000.0f;
    if (!game_instance.is_alive(nickname)) {
        client.set_nickname("");
        return "d";
    }
    game_instance.move_player(nickname, {x, y}, time);

    if (game_instance.is_alive(nickname)) return "a" + game_instance.get_player_segments(nickname);
    else {
        client.set_nickname("");
        return "d";
    }
}

std::string snek::server::new_player_request(snek::client_handler& client, const std::string& request) {
    if (game_instance.player_count() > config.get_uint64("max_players")) return "nf"; // not connected - full

    const std::string& nickname = request;
    if (game_instance.nickname_taken(nickname)) return "nt"; // not connected - nickname taken

    client.set_nickname(request);
    game_instance.add_player(nickname);
    return "y" + game_instance.player_position_str(nickname);
}

std::string snek::server::other_players_request(snek::client_handler& client, const std::string&) {
    const std::string& client_nickname = client.get_nickname();
    std::stringstream ss;
    ss << "p" << game_instance.player_count() - 1 << "n";
    for (const auto& [nickname, player] : game_instance.get_players()) {
        if (nickname == client_nickname) continue;
        ss << nickname << " " << player.get_segments().size() << "s"
           << game_instance.get_player_segments(nickname);
    }
    return ss.str();
}

std::string snek::server::food_request(snek::client_handler&, const std::string&) {
    return game_instance.get_food_str();
}

std::string snek::server::handle_request(snek::client_handler& client, const std::string& request) {
#ifdef SNEK_DEBUG
    std::cout << "received data from client " << client.get_socket() << ": " << request
              << " (" << request.size() << ") bytes" << std::endl;
#endif
    const std::string command = request.substr(0, COMMAND_LENGTH),
            argument = request.substr(COMMAND_LENGTH, request.size() - COMMAND_LENGTH - 1);
    if (requests.contains(command)) return (this->*requests[command])(client, argument) + "\n";
    return "e\n";
}

void snek::server::close_client(std::vector<snek::client_handler>::iterator& client, std::vector<pollfd>& poll_events) {
    close(client->get_socket());
    poll_events.erase(poll_events.begin() + (client - client_sockets.begin() + 1));
    game_instance.remove_player(client->get_nickname());
    client_sockets.erase(client);
    --client;
}

bool snek::server::handle_client(std::vector<snek::client_handler>::iterator& client,
                                 std::vector<pollfd>& poll_events, int& ready_events) {

    bool ready_events_decrement = true;

    if (poll_events[client - client_sockets.begin() + 1].revents & POLLIN) {
        ready_events_decrement = false;
        ready_events--;
        char buffer[100]{0};
        ssize_t bytes_received = recv(client->get_socket(), buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) std::cout << "Client disconnected: " << client->get_socket() << std::endl;
            else perror("recv");
            close_client(client, poll_events);
            return false;
        }

        const std::string response = handle_request(*client, buffer);
#ifdef SNEK_DEBUG
        std::cout << "Sending response to client " << client->get_socket() << ": " << response
                          << " (" << response.size() << ") bytes" << std::endl;
#endif
        client->send_data(response);
        client->update_activity_time();
    }

    if (client->has_message_to_send() and poll_events[client - client_sockets.begin() + 1].revents & POLLOUT) {
        if (ready_events_decrement) ready_events--;
        const std::string& message = client->get_message();
        ssize_t bytes_sent = send(client->get_socket(), message.c_str(), message.size(), 0);

        if (bytes_sent > 0) {
#ifdef SNEK_DEBUG
            std::cout << "Wysłano wiadomość do klienta: " << client->get_socket() << std::endl;
#endif
            if (client->get_nickname().empty()) { close_client(client, poll_events); }
        }
        else if (bytes_sent == 0) {
#ifdef SNEK_DEBUG
            std::cout << "Połączenie zostało zamknięte przez klienta: " << client->get_socket() << std::endl;
#endif
            close_client(client, poll_events);
        }
        else {
            perror("send");
            close_client(client, poll_events);
        }
    }
    return true;
}

void snek::server::loop() {

    while (true) {
        std::vector<pollfd> poll_events;
        pollfd server_poll_fd{.fd = server_socket, .events = POLLIN, .revents = 0};
        poll_events.push_back(server_poll_fd);

        for (const auto& client : client_sockets) {
            pollfd client_poll_fd{.fd = client.get_socket(), .events =
            short(client.has_message_to_send() ? POLLIN | POLLOUT : POLLIN), .revents = 0};
            poll_events.push_back(client_poll_fd);
        }

        int ready_events = poll(poll_events.data(), poll_events.size(),
                                client_sockets.empty() ? -1 : config.get_int32("client_timeout"));
        if (ready_events < 0) {
            perror("poll");
            break;
        }

        if (poll_events[0].revents & POLLIN) ready_events--;

        for (auto client = client_sockets.begin(); ready_events > 0 and client != client_sockets.end(); ++client)
            if (not handle_client(client, poll_events, ready_events)) continue;

        if (client_sockets.size() < config.get_uint64("max_connections") and poll_events[0].revents & POLLIN) {
            sockaddr_in client_addr{};
            socklen_t client_addr_len = sizeof(client_addr);
            int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
            if (client_socket < 0) {
                perror("accept");
                //continue;
            }
            else {
#ifdef SNEK_DEBUG
                std::cout << "new client_handler added" << std::endl;
#endif
                client_sockets.emplace_back(client_socket);
            }
        }

        for (auto it = client_sockets.begin(); it != client_sockets.end(); ++it) {
            if (it->get_time_passed_from_last_activity().count() > config.get_int32("client_timeout")) {
                close_client(it, poll_events);
#ifdef SNEK_DEBUG
                std::cout << " Client timeout yeet! " << std::endl;
#endif
            }
        }

    }

    for (const auto& client : client_sockets) close(client.get_socket());
}

void snek::server::start() {

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        std::exit(-1);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config.get_int32("port"));
    server_addr.sin_addr = {.s_addr = INADDR_ANY};

    int reuse = true;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        close(server_socket);
        std::exit(-1);
    }

    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        std::exit(-1);
    }

    if (listen(server_socket, config.get_int32("max_connections")) < 0) {
        perror("listen");
        close(server_socket);
        std::exit(-1);
    }

    const std::string ip = snek::get_local_ip();
    if (not ip.empty()) std::cout << "Server is running on: " << ip << ':' << config.get_string("port") << std::endl;
    else std::cerr << "Could not get local IP address" << std::endl;

    loop();

    close(server_socket);
}




