// sender for SHM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "/my_ipc_memory"
#define SHM_SIZE 100

int main() {
    int shm_fd;
    char *shared_mem;
    char input[SHM_SIZE];

    // create SHM
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // size of SHM
    ftruncate(shm_fd, SHM_SIZE);

    // M mapping
    shared_mem = mmap(NULL, SHM_SIZE,
                      PROT_WRITE,
                      MAP_SHARED,
                      shm_fd, 0);

    //input
    printf("enter message: ");
    fgets(input, sizeof(input), stdin);

    
    snprintf(shared_mem, SHM_SIZE, "%s", input);

    printf("data written to shared memory\n");

    munmap(shared_mem, SHM_SIZE);
    close(shm_fd);

    return 0;
}