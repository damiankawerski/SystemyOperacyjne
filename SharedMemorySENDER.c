//
// Created by damian on 6/7/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234
#define SEM_NAME "/semaphore"

int main() {
    int shmid;
    char* shmaddr;

    // Wspólna pamięć
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if(shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Przyłączenie do pamięci
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if(sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    char* cieplo = "CIEPLO";
    char* zimno = "ZIMNO";

    for(int i = 0 ; i < 10 ; i++) {
        sem_wait(sem);
        if(i % 2 == 0) {
            strcpy(shmaddr, cieplo);
        } else {
            strcpy(shmaddr, zimno);
        }
        sem_post(sem);
        sleep(1);
    }

    shmdt(shmaddr);
    sem_close(sem);
    sem_unlink(SEM_NAME);
}

//Komendy

//gcc -o sender sender.c -lrt -pthread
//gcc -o receiver receiver.c -lrt -pthread