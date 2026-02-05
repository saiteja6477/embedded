#include <stdio.h>              // Standard I/O functions
#include <stdlib.h>             // For exit()
#include <string.h>             // For memset and string operations
#include <unistd.h>             // For close(), read(), write()
#include <arpa/inet.h>          // For inet_pton(), htons(), etc.
#include <netinet/in.h>         // For sockaddr_in
#include <sys/socket.h>         // For socket functions

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};    // Buffer to store incoming message from server

    // 1. Create a socket (IPv4, TCP)
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    

    // 2. Set up the server address structure
    server_addr.sin_family = AF_INET;            // IPv4
    server_addr.sin_port = htons(8080);          // Port 8080 (host to network byte order)

    // 3. Convert and set the IP address (127.0.0.1 => localhost)
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // 4. Connect to the server
    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ;

    // 5. Send a message to the server
    char *msg = "hello server";
    send(sock_fd, msg, strlen(msg), 0);
    printf("message sent to server.\n");

    // 6. Read response from server
    read(sock_fd, buffer, sizeof(buffer));
    printf("server response: %s\n", buffer);

    // 7. Close the socket
    close(sock_fd);

    return 0;
}