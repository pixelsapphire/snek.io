#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cctype>

#define SERVER_PORT 8080
#define MAX_CLIENTS 20

int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(1);
    }

    // Bind the socket to a port
    sockaddr_in server_addr{.sin_family = AF_INET, .sin_port = htons(SERVER_PORT), .sin_addr={.s_addr=INADDR_ANY}};

    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // Listen for connections
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(1);
    }

    // Create a list of client sockets
    int client_sockets[MAX_CLIENTS];
    for (int& client_socket : client_sockets) client_socket = -1;

    // Accept connections and handle client requests
    while (1) {
        // Accept a connection from a client
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        // Send "Hello" to the client
        char hello_message[10];
        strcpy(hello_message, "Hello\n");
        if (send(client_socket, hello_message, strlen(hello_message), 0) < 0) {
            perror("send");
            close(client_socket);
            continue;
        }

        // Add the client socket to the list
        for (int& i : client_sockets)
            if (i == -1) {
                i = client_socket;
                break;
            }

        // Handle client requests
        while (1) {
            // Receive a message from the client
            char message[100];
            ssize_t bytes_received = recv(client_socket, message, sizeof(message), 0);
            if (bytes_received < 0) {
                perror("recv");
                close(client_socket);
                for (int& i : client_sockets)
                    if (i == client_socket) {
                        i = -1;
                        break;
                    }
                break;
            }

            // Check if the client has disconnected
            if (bytes_received == 0) {
                // Client has disconnected
                close(client_socket);
                for (int& i : client_sockets)
                    if (i == client_socket) {
                        i = -1;
                        break;
                    }
                break;
            }

            // Capitalize the message
            for (int i = 0; i < bytes_received; i++) message[i] = char(toupper(message[i]));

            // Send the message back to the client
            if (send(client_socket, message, bytes_received, 0) < 0) {
                perror("send");
                close(client_socket);
                for (int& i : client_sockets)
                    if (i == client_socket) {
                        i = -1;
                        break;
                    }
                break;
            }
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}