#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

void forkPattern1(int numThings) {
    pid_t pids[numThings];
    for (int i = 0; i < numThings; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("process %d beginning\n", i + 1);
            sleep(rand()%5);
            printf("process %d exiting\n", i + 1);
            exit(0);
        } else {
            pids[i] = pid;
        }
    }
    for (int i = 0; i < numThings; i++) {
        waitpid(pids[i], NULL, 0);
    }
}


void forkPattern2(int numThings) {
    pid_t pid = getpid();
    for (int i = 0; i < numThings; i++) {
        pid_t child = fork();
        if (child == 0) {
            printf("process %d beginning\n", i + 1);
            sleep(rand()%5);
            if (i < numThings - 1) {
                printf("process %d creating process %d\n", i + 1, i + 2);
                sleep(rand()%5);
            }
            wait(NULL);
            printf("process %d exiting\n", i + 1);
        } else {
            wait(NULL);
            break;
        }
    }
    exit(0);
}


int main(int argc, char *argv[]) {
    srand(time(NULL)); 
    if (atoi(argv[2])== 1) {
        forkPattern1(atoi(argv[1]));
    } else if (atoi(argv[2]) == 2) {
        forkPattern2(atoi(argv[1]));
    }
    return 0;
}