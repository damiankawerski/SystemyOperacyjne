#include <iostream>
#include "Lab5.h"
#include "Lab4.h"
#include "Lab6.h"
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char *fifoPath = "/tmp/fifo";
    pid_t pid1, pid2;

    mkfifo(fifoPath, 0666);
    pid1 = fork();

    if (pid1 == 0) {
        int fd = open(fifoPath, O_WRONLY);
        write(fd, "HALLO!", 7);
        close(fd);
    } else if (pid1 > 0) {
        pid2 = fork();

        if (pid2 == 0) {
            wait(&pid1);

            char str[7];

            int fd = open(fifoPath, O_RDONLY);
            read(fd, str, 7);
            printf("%s\n", str);
            close(fd);
        }
    }
}