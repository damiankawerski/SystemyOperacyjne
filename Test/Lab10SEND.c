#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

int main() {
    int shmid;
    char *shmaddr;
    int status;
    scanf("%d", &status);

    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid < 0) {
        perror("shmid");
        exit(1);
    }

    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    while (status != 0) {
        strcpy(shmaddr, "CIEPLO");
        sleep(1);
        strcpy(shmaddr, "ZIMNO");
        sleep(1);
    }

    shmdt(shmaddr);
    return 0;
}