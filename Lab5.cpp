//
// Created by damian on 14.04.24.
//

#include "Lab5.h"

#include <stdio.h>


int max1(int *a, int *b) {
    return *a > *b ? *a : *b;
}

int* max2(int *a, int *b) {
    return *a > *b ? a : b;
}

int* max3(int *a, int *b) {
    return a > b ? a : b;
}

void max4(int *a, int *b) {
    if(*a < *b) {
        return;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Lab5() {
    int a = 10;
    int b = 5;
    printf("a = %d, b = %d\n", a, b);
    max4(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    max4(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    return;
}