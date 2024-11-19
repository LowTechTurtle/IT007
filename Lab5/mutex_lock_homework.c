#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex;
int x = 0;

void* processA(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("%d\n", x);
        pthread_mutex_unlock(&mutex);
    }
}

void* processB(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("%d\n", x);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t threadA, threadB;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threadA, NULL, processA, NULL);
    pthread_create(&threadB, NULL, processB, NULL);

    for (int i = 0; i < 100; i++) {
        sleep(0.5);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}
