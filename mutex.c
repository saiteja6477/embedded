#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
 
pthread_t t1, t2, t3, t4;
 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
 
void* count1(void *arg);
void* count2(void *arg);
void* count3(void *arg);
void* count4(void *arg);
 
int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0;
 
void* count1(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (c1 < 20) {
            c1++;
         
         printf("c1 = %d\n", c1);
 
            if (c1 == 10) {
                pthread_create(&t4, NULL, count4, NULL);
                printf("\n");
            }
 
            if (c1 == 20) {
                c2++;
                printf("c2 = %d\n", c2);
                c1 = 0;
                c3 = 0;
                c4 = 0;
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
 
void* count4(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (c4 < 5) {
            c4++;
            printf("\nc4 = %d\n", c4);
 
            if (c4 == 5) {
                c4 = 0;
                pthread_create(&t3, NULL, count3, NULL);
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
 
void* count3(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (c3 < 5) {
            c3++;
            printf("c3 = %d\n", c3);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
 
void* count2(void *arg) {
    while (1) {
        sleep(1);
        if(c2 == 5){
            pthread_cancel(t1);
            pthread_cancel(t2);
            pthread_cancel(t3);
            pthread_cancel(t4);
            exit(1);
        }
    }
    return NULL;
}
 
int main() {
    pthread_create(&t1, NULL, count1, NULL);
    pthread_create(&t2, NULL, count2, NULL);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
 
   return 0;
}