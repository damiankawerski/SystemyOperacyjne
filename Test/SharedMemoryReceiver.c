// receiver.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024
#define SEM_NAME "/semaphore"

int main() {
    int shmid;
    char *shmaddr;
    int status;

    // Read status from input
    scanf("%d", &status);

    // Get shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
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

    // Open semaphore
    sem_t *sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Read from shared memory with semaphore protection
    while (status != 0) {
        sem_wait(sem);
        if (strcmp(shmaddr, "CIEPLO") == 0 || strcmp(shmaddr, "ZIMNO") == 0) {
            printf("Odczytano poprawny napis: %s\n", shmaddr);
        } else {
            printf("Błąd: odczytano niepoprawny napis: %s\n", shmaddr);
        }
        sem_post(sem);
        sleep(1);
    }

    // Detach from shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Close semaphore
    sem_close(sem);

    return 0;
}
