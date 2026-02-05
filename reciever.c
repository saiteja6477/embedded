#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/my_queue"
#define MAX_MSG_SIZE 256


int main() {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY | O_NONBLOCK, 0644, &attr);

    
    char buffer[MAX_MSG_SIZE];
    
    
    mq_receive(mq, buffer, MAX_MSG_SIZE, NULL);
    printf("%s\n",buffer);

    printf(" received successfully\n");
    
    mq_close(mq);
    
    return 0;
}