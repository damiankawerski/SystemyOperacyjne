//
// Created by damian on 22.04.24.
//

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>


 void zadanie1() {
     int fd[2];
     pid_t pid1, pid2;

     pipe(fd);
     pid1 = fork();

     if (pid1 == 0) {
         write(fd[1], "HALLO!", 7);
         close(fd[1]);
     } else if (pid1 > 0) {
         pid2 = fork();

         if (pid2 == 0) {
             wait(&pid1);

             char str[7];
             read(fd[0], str, 7);
             printf("%s\n", str);
         }
     }
 }

 int main() {
     int fd[2];
     pid_t pid1, pid2, pid3;

     pipe(fd);
     pid1 = fork();

     if (pid1 == 0) {
         write(fd[1], "HALLO!", 7);
         close(fd[1]);
     }

     pid2 = fork();
     if (pid2 == 0) {
         write(fd[1], "MASLO!", 7);
         close(fd[1]);
     }


     pid3 = fork();

     if (pid3 == 0) {
         char str[7];
         while (read(fd[0], str, 7)) {
             printf("%s\n", str);
         }
         close(fd[0]);
     }

     waitpid(pid1, NULL, 0);
     waitpid(pid2, NULL, 0);
     waitpid(pid3, NULL, 0);

     return 0;
 }