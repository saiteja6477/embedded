#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    int sfd, cfd;
    struct sockaddr_in saddr, caddr;
    socklen_t alen = sizeof(caddr);
    char buf[1024] = {0};

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8080);
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(sfd, 5);

    printf("server listening on 8080...\n");

    cfd = accept(sfd, (struct sockaddr *)&caddr, &alen);

    printf("connection from %s:%d\n",
           inet_ntoa(caddr.sin_addr),
           ntohs(caddr.sin_port));

    read(cfd, buf, sizeof(buf));
    printf("client: %s\n", buf);

    char *msg = "hi client!";
    send(cfd, msg, strlen(msg), 0);

    close(cfd);
    close(sfd);

    return 0;
}