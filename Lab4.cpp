//
// Created by damian on 14.04.24.
//

#include "Lab4.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void filePrinter(const char* fileName, const char* mode) {
    srand(time(0));
    FILE* file = fopen(fileName, mode);
    if(!file) {
        printf("File does not exist\n");
        return;
    }
    for(int i = 0 ; i < atoi(getenv("LAB4ENV")) ; i++) {
        fprintf(file, "%d ", rand() % 1000);
    }
    fclose(file);
}

int charCounter(const char* path) {
    FILE* file = fopen(path, "r");
    if(!file) {
        printf("Error opening file\n");
        return 0;
    }
    int counter = 0;
    while(fgetc(file) != EOF) {
        counter++;
    }
    return counter;
}

int numberCounter(const char* path) {
    FILE* file = fopen(path, "r");
    if(!file) {
        printf("Error opening file\n");
        return 0;
    }
    int number;
    int counter = 0;
    while(fscanf(file, "%d", &number) != EOF) {
        counter++;
    }
    return counter;
}

void Lab4(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Not enough parameters/n");
        return;
    }

    int counter = charCounter(argv[1]);

    if(counter > 10) {
        filePrinter(argv[1], "a");
    }
    else {
        filePrinter(argv[1], "w");
    }

    printf("Number of numbers in file: %d\n", numberCounter(argv[1]));

    return;
}