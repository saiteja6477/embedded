#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
int flag = 1; 

void* thread1(void* arg) {
    while (count < 100) {
        pthread_mutex_lock(&mutex);
        
        
        while (flag != 1 && count < 100) {
            pthread_cond_wait(&cond1, &mutex);
        }
        
        if (count < 100) {
            count++;
            printf("thread1: %d\n", count);
            flag = 2;
            sleep(1);
            pthread_cond_signal(&cond2); 
        }
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* thread2(void* arg) {
    while (count < 100) {
        pthread_mutex_lock(&mutex);
        
        
        while (flag != 2 && count < 100) {
            pthread_cond_wait(&cond2, &mutex);
        }
        
        if (count < 100) {
            count++;
            printf("thread2: %d\n", count);
            flag = 1;
            sleep(1);
            pthread_cond_signal(&cond1);  
        }
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("count reached 100\n");
    
    return 0;
}
