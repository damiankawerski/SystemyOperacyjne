////
//// Created by damian on 6/7/24.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>
//#include <unistd.h>
//#include <wait.h>
//
//#define MSGSZ 128
//
//struct msg_buffer {
//    long msg_type;
//    char msg_content[MSGSZ];
//};
//
//void sender(int msgid) {
//    struct msg_buffer msg;
//    msg.msg_type = 1;
//    strcpy(msg.msg_content, "HELLO");
//
//    if(msgsnd(msgid, &msg, sizeof(msg.msg_content), 0) == -1) {
//        perror("send");
//        exit(1);
//    }
//}
//
//void receiver(int msgid) {
//    struct msg_buffer msg;
//
//    if(msgrcv(msgid, &msg, sizeof(msg.msg_content),1, 0) == -1) {
//        perror("receive");
//        exit(1);
//    }
//
//    printf("%s\n", msg.msg_content);
//
//    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
//        perror("msgctl");
//        exit(1);
//    }
//}
//
//int main() {
//    key_t key;
//    int msgid;
//    const char *filepath = "/tmp/ftokfile";
//
//    FILE *file = fopen(filepath, "w");
//    if (!file) {
//        perror("fopen");
//        exit(1);
//    }
//    fclose(file);
//
//    if((key = ftok(filepath, 65)) == -1) {
//        perror("ftok");
//        exit(1);
//    }
//
//    if((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
//        perror("msgget");
//        exit(1);
//    }
//
//    pid_t pid = fork();
//
//    if(pid < 0) {
//        perror("fork");
//        exit(1);
//    } else if(pid == 0) {
//        sleep(1);
//        receiver(msgid);
//    } else {
//        sender(msgid);
//        wait(NULL);
//    }
//
//    return 0;
//}