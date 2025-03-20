#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type 'exit' to disconnect.\n");

    // Communicate with the server
    while (1) {
        printf("You: ");
        fgets(message, BUFFER_SIZE, stdin);

        // Remove trailing newline character from input
        message[strcspn(message, "\n")] = 0;

        // Check if the user wants to exit
        if (strcmp(message, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Send message to server
        send(sock, message, strlen(message), 0);

        // Read response from server
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(sock, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            printf("Server disconnected\n");
            break;
        }
        printf("Server: %s\n", buffer);
    }

    // Close the socket
    close(sock);
    return 0;
}