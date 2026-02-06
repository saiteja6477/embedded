//SEM RD
#include <stdio.h>
#include <stdlib.h>
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

    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    shared_mem = mmap(NULL, SHM_SIZE,
                      PROT_READ,
                      MAP_SHARED,
                      shm_fd, 0);

    sem_t *sem = sem_open(SEM_NAME, 0);

   
    sem_wait(sem);

    printf("reader read: %s\n", shared_mem);

  
    sem_post(sem);

    munmap(shared_mem, SHM_SIZE);
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);

    return 0;
}