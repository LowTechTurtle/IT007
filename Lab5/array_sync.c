#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

int arr[1421] = {0};
int count = 0;
sem_t sem;

void* producer(void* arg) {
    srand(23521421);
    int r;
    while (true) {
        sem_wait(&sem);
        if (count < 1421) {
            arr[count] = rand();
            count++;
        }
        printf("Producer: Count is %d\n", count);
//        sleep(rand()/RAND_MAX);
        sem_post(&sem);
    }
}

void* consumer(void* arg) {
    while (true) {
        sem_wait(&sem);
        if (count == 0) {
            printf("There's nothing in a\n");
        }
        if (count > 0)
            count--;
        printf("Consumer: Count is %d\n", count);
//        sleep(rand()/RAND_MAX);
        sem_post(&sem);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    sem_init(&sem, 0, 1);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    for (int i = 0; i < 60; i++) {
        sleep(0.5);
    }
//    sem_destroy(&sem);
    return 0;
}