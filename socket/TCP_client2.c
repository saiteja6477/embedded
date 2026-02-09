// TCP Client  
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define PORT 5000 
#define MAXLINE 1024 
int main() 
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    char* message = "hello Server"; 
    struct sockaddr_in servaddr; 

    int n, len; 
     
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 

     
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

   connect(sockfd, (struct sockaddr*)&servaddr, 
                            sizeof(servaddr)) ;
    } 

    memset(buffer, 0, sizeof(buffer)); 
    strcpy(buffer, "hello Server"); 
    write(sockfd, buffer, sizeof(buffer)); 
    printf("message from server: "); 
    read(sockfd, buffer, sizeof(buffer)); 
    puts(buffer); 
    close(sockfd); 
}