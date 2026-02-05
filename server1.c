#include <stdio.h>              // Standard I/O functions
#include <stdlib.h>             // For exit()
#include <string.h>             // For memset and string operations
#include <unistd.h>             // For close()
#include <arpa/inet.h>          // For inet_ntoa, htons, etc.
#include <netinet/in.h>         // For sockaddr_in
#include <sys/socket.h>         // For socket functions

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    char buffer[1024] = {0};

    // 1. Create a TCP socket (IPv4, stream-based)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
   

    // 2. Set server address structure
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_port = htons(8080);         // Port 8080 (converted to network byte order)
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Bind to any available interface (localhost or network)

    // 3. Bind the socket to the specified IP and port
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ;

    // 4. Listen for incoming connections (maximum 5 queued connections)
    listen(server_fd, 5) ;

    printf("Server is listening on port 8080...\n");

    // 5. Accept a new client connection
    client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
   

    // 6. Print client's IP and port
    printf("connection accepted from %s:%d\n",
           inet_ntoa(client_addr.sin_addr),       // Convert client's IP to human-readable string
           ntohs(client_addr.sin_port));          // Convert client's port to host byte order

    // 7. Receive data from the client
    read(client_socket, buffer, sizeof(buffer));
    printf("client says: %s\n", buffer);

    // 8. Send a response to the client
    char *msg = "hi client!";
    send(client_socket, msg, strlen(msg), 0);

    // 9. Close both client and server sockets
    close(client_socket);
    close(server_fd);

    return 0;
}