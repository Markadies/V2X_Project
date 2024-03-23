#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    const char *message = "Hello from C++!";
    send(client_socket, message, strlen(message), 0);

    char buffer[1024] = {0};
    recv(client_socket, buffer, 1024, 0);
    std::cout << "Received: " << buffer << std::endl;

    close(client_socket);

    return 0;
}

