
//Server_Socket_Programming

#include <iostream>                                                  // For input-output stream
#include <sys/socket.h>                                              // For socket functions
#include <netinet/in.h>                                              // For sockaddr_in structure
#include <unistd.h>                                                  // For read() and close()
#include <cstring>                                                   // For string functions

#define PORT 8080                                                    // Define port number

int main() {
    int server_fd, client_fd;                                        // File descriptors for server and client
    struct sockaddr_in address;                                      // Structure to hold server address
    char buffer[1024];                                               // Buffer to store messages

    server_fd = socket(AF_INET, SOCK_STREAM, 0);                     // Create a TCP socket

    address.sin_family = AF_INET;                                    // Set address family to IPv4
    address.sin_addr.s_addr = INADDR_ANY;                            // Accept connections from any IP
    address.sin_port = htons(PORT);                                  // Convert port to network byte order

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));    // Bind socket to IP and port

    listen(server_fd, 1);                                            // Listen for client connections
    std::cout << "Server listening on port " << PORT << std::endl;   // Print listening message

    client_fd = accept(server_fd, nullptr, nullptr);                 // Accept incoming client connection

    while (true) {
        int n = read(client_fd, buffer, sizeof(buffer));             // Read message from client
        buffer[n] = '\0';                                            // Null-terminate received message
        std::cout << "Client: " << buffer << std::endl;              // Display client’s message

        std::cout << "Server: ";                                     // Display prompt for server reply
        std::string msg;                                             // Declare string variable for reply
        std::getline(std::cin, msg);                                 // Take server’s reply input
        send(client_fd, msg.c_str(), msg.length(), 0);               // Send reply to client
    }

    close(client_fd);                                                // Close client connection
    close(server_fd);                                                // Close server socket
    return 0;                                                        // End program
}
