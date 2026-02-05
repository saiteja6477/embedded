#include <stdio.h>
#include <pthread.h>

char shared_data[100];

void* writer(void* arg) {
    sprintf(shared_data, "Hello from writer thread");
    return NULL;
}

void* reader(void* arg) {
    printf("Reader sees: %s\n", shared_data);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, writer, NULL);
    pthread_create(&t2, NULL, reader, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}