// sender.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234
#define SEM_NAME "/semaphore"

int main() {
    int shmid;
    char *shmaddr;
    int status;

    // Read status from input
    scanf("%d", &status);

    // Create shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Open or create semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Write to shared memory with semaphore protection
    while (status != 0) {
        sem_wait(sem);
        strcpy(shmaddr, "CIEPLO");
        sem_post(sem);
        sleep(1);

        sem_wait(sem);
        strcpy(shmaddr, "ZIMNO");
        sem_post(sem);
        sleep(1);
    }

    // Detach from shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Close and unlink semaphore
    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}
