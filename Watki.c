////
//// Created by damian on 6/7/24.
////
//
//#include <pthread.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <stdio.h>
//
//int global_number = 0;
//pthread_mutex_t mutex_id;
//
//void *print_array(void *arg) {
//
//    pthread_mutex_lock(&mutex_id);
//
//    int* arr = (int*)arg;
//    for(int i = 0 ; i < 10 ; i++) {
//        printf("Liczba: %d", i);
//        global_number++;
//        sleep(1);
//
//    }
//
//    pthread_mutex_unlock(&mutex_id);
//
//    pthread_exit(NULL);
//}
//
//int main() {
//    pthread_t thread;
//
//    if(pthread_mutex_init(&mutex_id, NULL)) {
//        perror("init");
//        return -1;
//    }
//
//    if(pthread_create(&thread, NULL, print_array, NULL)) {
//        perror("create");
//        return -1;
//    }
//
//    pthread_mutex_lock(&mutex_id);
//    for(int i = 0 ; i < 10 ; i++) {
//        global_number++;
//        sleep(1);
//    }
//
//    pthread_mutex_unlock(&mutex_id);
//
//    if (pthread_join(thread, NULL)) {
//        perror("Error occured on pthread_join");
//        return -1;
//    }
//
//    pthread_mutex_destroy(&mutex_id);
//
//    printf("Number = %d\n", global_number);
//
//    return 0;
//}
