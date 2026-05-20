// Client_Socket_Programming

#include <iostream>                                                  // For input-output stream
#include <sys/socket.h>                                              // For socket functions
#include <arpa/inet.h>                                               // For inet_addr and htons
#include <unistd.h>                                                  // For close() and read()
#include <cstring>                                                   // For string operations

#define PORT 8080                                                    // Define port number

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);                      // Create a TCP socket
    struct sockaddr_in serv_addr;                                    // Define server address structure
    char buffer[1024];                                               // Buffer to store received data

    serv_addr.sin_family = AF_INET;                                  // Set address family to IPv4
    serv_addr.sin_port = htons(PORT);                                // Convert port to network byte order
    serv_addr.sin_addr.s_addr = inet_addr("172.18.9.117");           // Set server IP address

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));  // Connect to server

    while (true) {
        std::cout << "Client: ";                                     // Display prompt for client message
        std::string msg;                                             // Declare string variable for message
        std::getline(std::cin, msg);                                 // Take input from user
        send(sock, msg.c_str(), msg.length(), 0);                    // Send message to server

        int n = read(sock, buffer, sizeof(buffer));                  // Read server’s reply
        buffer[n] = '\0';                                            // Null-terminate received data
        std::cout << "Server: " << buffer << std::endl;              // Display server’s reply
    }

    close(sock);                                                     // Close the socket connection
    return 0;                                                        // End program
}
