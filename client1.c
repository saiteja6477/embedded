#include <stdio.h>              
#include <stdlib.h>            
#include <string.h>             
#include <unistd.h>             
#include <arpa/inet.h>         
#include <netinet/in.h>        
#include <sys/socket.h>         

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};    


    // 1. Create a socket 
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    

    
    server_addr.sin_family = AF_INET;            // IPv4
    server_addr.sin_port = htons(8080);          // Port 


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