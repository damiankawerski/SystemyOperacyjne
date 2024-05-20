//
// Created by damian on 14.04.24.
//


#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

 //For linux

void zadanie1() {
    pid_t pid1, pid2, pid3, pid4;
    int st1, st2, st3, st4;

    pid1 = fork();
    if(pid1 == 0) {
        cout << "ID pierwsego procesu: " << getpid() << endl;
        pid2 = fork();
        if(pid2 == 0) {
            cout << "ID potomka pierwszego procesu: " << getpid() << endl;
        }
        waitpid(pid2, &st2, 0);
        exit(0);
    }

    pid3 = fork();
    if(pid3 == 0) {
        cout << "ID drugiego procesu: " << getpid() << endl;
        pid4 = fork();
        if(pid4 == 0) {
            cout << "ID potomka drugiego procesu: " << getpid() << endl;
        }
        waitpid(pid4, &st4, 0);
        exit(0);
    }

    waitpid(pid1, &st1, 0);
    waitpid(pid3, &st3, 0);
}

void zadanie2() {
    cout << "Początek" << endl;
    pid_t pid = fork();
    if(pid == 0) {
        execlp("ls", "ls", "-al", NULL);
    }
    waitpid(pid, 0, 0);
    cout << "Koniec" << endl;
}

void zadanie3(const char* fileName) {
    srand(time(0));
    FILE* file = fopen(fileName, "a+");
    for(int i = 0 ; i < 5 ; i++) {
        char string[6];
        for(int j = 0 ; j < 5 ; j++) {
            char randomChar = 'a' + rand() % 26;
            randomChar += rand() % 2 ? 0 : 'A' -'a';
            string[j] = randomChar;
            string[j + 1] = '\0';
        }
        fprintf(file, "%s\n", string);
    }


    pid_t pid1, pid2;
    int st1, st2;

    pid1 = fork();
    if(pid1 == 0) {
        for(int i = 0 ; i < 5 ; i++) {
            char string[6];
            for(int j = 0 ; j < 5 ; j++) {
                char randomChar = 'a' + rand() % 26;
                randomChar += rand() % 2 ? 0 : 'A' -'a';
                string[j] = randomChar;
                string[j + 1] = '\0';
            }
            fprintf(file, "%s\n", string);
        }
    }

    pid2 = fork();
    if(pid2 == 0) {
        for(int i = 0 ; i < 5 ; i++) {
            char string[6];
            for(int j = 0 ; j < 5 ; j++) {
                char randomChar = 'a' + rand() % 26;
                randomChar += rand() % 2 ? 0 : 'A' -'a';
                string[j] = randomChar;
                string[j + 1] = '\0';
            }
            fprintf(file, "%s\n", string);
        }
    }

    waitpid(pid1, &st1, 0);
    waitpid(pid2, &st2, 0);

    fclose(file);
}


void Lab6() {
    //zadanie1();
    zadanie2();
    //zadanie3("/home/damian/GitHub/SystemyOperacyjne/Lab6/test.txt");
}
