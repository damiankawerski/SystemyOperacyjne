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
    char *shmaddr;

    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if(shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shmaddr = shmat(shmid, NULL, 0);
    if(shmaddr == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    sem_t *sem = sem_open(SEM_NAME, 0);
     if(sem == SEM_FAILED) {
         perror("sem_open");
         exit(1);
     }

     while(1) {
         sem_wait(sem);

         if(strcmp("CIEPLO", shmaddr) == 0 || strcmp("ZIMNO", shmaddr) == 0) {
             printf("Odczytano: %s", shmaddr);
         } else {
             printf("Zły napis");
         }
         sem_post(sem);
         sleep(1);
     }

     shmdt(shmaddr);
    sem_close(sem);

    return 0;
}