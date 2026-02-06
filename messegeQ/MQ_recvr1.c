//MQ RECIEVER
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MQ_NAME "/my_queue"
#define MAX_SIZE 100

int main()
{
    mqd_t mq;
    char buffer[MAX_SIZE];
    unsigned int priority;

    
    mq = mq_open(MQ_NAME, O_RDONLY);

    
    mq_receive(mq, buffer, MAX_SIZE, &priority);

    printf("receiver message  recieved: %s\n", buffer);

    mq_close(mq);
    mq_unlink(MQ_NAME);   

    return 0;
}