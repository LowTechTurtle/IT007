#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

void handle_sigint(int sig) {
    printf("\ncount.sh has stopped\n");
    kill(pid, SIGINT);
    exit(0);
}

int main() {
    printf("Welcome to IT007, I am 23521421!\n");

    pid = fork();

    if (pid == 0) {
        execl("./count.sh", "./count.sh", "120", "NULL");
        exit(1);
    } else {
        signal(SIGINT, handle_sigint);

        wait(NULL);
    }
    return 0;
}

