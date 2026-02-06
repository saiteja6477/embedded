//semaphore writer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_NAME "/shm_sem"
#define SEM_NAME "/sem_lock"
#define SHM_SIZE 100

int main() {
    int shm_fd;
    char *shared_mem;
    char input[SHM_SIZE];

    
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);

    shared_mem = mmap(NULL, SHM_SIZE,
                      PROT_WRITE,
                      MAP_SHARED,
                      shm_fd, 0);

    // sem with 1 means binary
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    
    printf("write data: ");
    fgets(input, sizeof(input), stdin);

    
    sem_wait(sem);

    snprintf(shared_mem, SHM_SIZE, "%s", input);
    printf("writer written safely\n");

    
    sem_post(sem);

    munmap(shared_mem, SHM_SIZE);
    close(shm_fd);

    return 0;
}