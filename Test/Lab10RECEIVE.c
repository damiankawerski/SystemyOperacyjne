#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shmaddr;
    int status;
    scanf("%d", &status);
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
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
        if (strcmp(shmaddr, "CIEPLO") == 0 || strcmp(shmaddr, "ZIMNO") == 0) {
            printf("Odczytano poprawny napis: %s\n", shmaddr);
        } else {
            printf("Błąd: odczytano niepoprawny napis: %s\n", shmaddr);
        }
        sleep(1);
    }

    shmdt(shmaddr);

    return 0;
}