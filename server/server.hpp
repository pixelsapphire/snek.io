//
// Created by stas on 11.01.2024.
//

#ifndef SNEK_IO_SERVER_HPP
#define SNEK_IO_SERVER_HPP

#endif //SNEK_IO_SERVER_HPP


#include <iostream>
#include <cstring>
#include <winsock2.h>
#include "cliencior.hpp"
#include <vector>

#pragma comment(lib, "ws2_32.lib")

class server_win {
private:
    const int clientLimit = 10;

public:
    const int port = 12345;
    const int timeoutSeconds = 5;

    int main() {
        // Inicjalizacja Winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Błąd podczas inicjalizacji Winsock" << std::endl;
            return -1;
        }

        // Ustawienia serwera
        //const int port = 12345;

        // Tworzenie gniazda serwera
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            std::cerr << "Błąd podczas tworzenia gniazda serwera" << std::endl;
            WSACleanup();
            return -1;
        }

        // Konfiguracja adresu serwera
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        // Powiązanie gniazda serwera z adresem
        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
            std::cerr << "Błąd podczas powiązywania gniazda serwera z adresem" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        }

        // Nasłuchiwanie na połączenia przychodzące
        if (listen(serverSocket, clientLimit) == SOCKET_ERROR) {
            std::cerr << "Błąd podczas nasłuchiwania na gnieździe serwera" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        }

        std::cout << "Serwer nasłuchuje na porcie " << port << std::endl;

        std::vector<Client> clients;

        // Akceptowanie połączeń
        while (true) {
            fd_set clientSockets;

            // Inicjalizacja listy gniazd klientów
            FD_ZERO(&clientSockets);
            FD_SET(serverSocket, &clientSockets);

            for (const auto& client : clients) {
                FD_SET(client.getSocket(), &clientSockets);
            }

            // Ustawienie timeout'u
            timeval timeout;
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;

            // Oczekiwanie na dostępność danych do odczytu na jednym z gniazd
            int result = select(0, &clientSockets, nullptr, nullptr, &timeout);
            if (result == SOCKET_ERROR) {
                std::cerr << "Błąd podczas używania funkcji select" << std::endl;
                break;
            }

            // Sprawdzenie czy serwer jest gotów do akceptowania nowego połączenia
            if (FD_ISSET(serverSocket, &clientSockets)) {
                sockaddr_in clientAddress{};
                int clientAddrLen = sizeof(clientAddress);

                // Akceptowanie połączenia
                SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);
                if (clientSocket == INVALID_SOCKET) {
                    std::cerr << "Błąd podczas akceptowania połączenia" << std::endl;
                } else {
                    std::cout << "Nowe połączenie od " << inet_ntoa(clientAddress.sin_addr)
                              << " na porcie " << ntohs(clientAddress.sin_port) << std::endl;

                    // Dodanie nowego klienta do listy
                    clients.emplace_back(clientSocket);
                }
            }

            // Przeszukanie listy klientów i obsługa zdarzeń
            for (auto& client : clients) {
                if (FD_ISSET(client.getSocket(), &clientSockets)) {
                    char buffer[1024];
                    memset(buffer, 0, sizeof(buffer));

                    // Odbieranie danych od klienta
                    int bytesReceived = recv(client.getSocket(), buffer, sizeof(buffer) - 1, 0);
                    if (bytesReceived == SOCKET_ERROR) {
                        std::cerr << "Błąd podczas odbierania danych od klienta" << std::endl;
                    } else if (bytesReceived == 0) {
                        std::cout << "Klient zamknął połączenie" << std::endl;
                        closesocket(client.getSocket());
                        // Usunięcie klienta z listy
                        clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
                    } else {
                        // Przetwarzanie odebranych danych
                        std::cout << "Odebrano wiadomość od klienta: " << buffer << std::endl;
                        // Aktualizacja czasu ostatniej aktywności
                        client.updateActivityTime();
                    }
                }

                // Sprawdzenie, czy klient nie wysłał wiadomości przez dłuższy czas
                time_t currentTime = time(nullptr);
                if (currentTime - client.getLastActivityTime() > 30) {
                    std::cout << "Zamykanie połączenia z klientem (brak aktywności)" << std::endl;
                    closesocket(client.getSocket());
                    // Usunięcie klienta z listy
                    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
                }
            }
        }

        // Zamykanie gniazda serwera i zwalnianie zasobów
        closesocket(serverSocket);
        WSACleanup();

        return 0;
    }
};