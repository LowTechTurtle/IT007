#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

void collatz_sequence(int n, int* buffer) {
    int index = 0;
    while (n != 1) {
        buffer[index++] = n;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }
    buffer[index++] = 1;
    buffer[index] = -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <positive integer>\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);

    if (n < 0) {
        printf("Negative integer\n");
        exit(1);
    }
    int shmid = shmget(IPC_PRIVATE, 1024 * sizeof(int), IPC_CREAT | 0666);

    int *shared_buffer = (int *)shmat(shmid, NULL, 0);
    pid_t pid = fork();
    if (pid == 0) {
        collatz_sequence(n, shared_buffer);
        shmdt(shared_buffer);
        exit(0);
    } else {
        wait(NULL);
        int i = 0;
        while (shared_buffer[i] != -1) {
            printf("%d ", shared_buffer[i]);
            i++;
        }
        printf("\n");
        shmdt(shared_buffer);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}

