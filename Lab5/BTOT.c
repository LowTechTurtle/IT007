#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6;
int w = 0, v = 0, y = 0, z = 0, ans = 0;

sem_t sem_c_d, sem_e, sem_g;

void* thread_cal_a(void* arg) {
    w = x1 * x2;
    printf("Calulated w = %d (a)\n", w);
    sem_post(&sem_e);
}

void* thread_cal_b(void* arg) {
    v = x3 * x4;
    printf("Calulated v = %d (b)\n", v);
    sem_post(&sem_c_d);
    sem_post(&sem_c_d);
}

void* thread_cal_c(void* arg) {
    sem_wait(&sem_c_d);
    y = v * x5;
    printf("Calulated y = %d (c)\n", y);
    sem_post(&sem_e);
}

void* thread_cal_d(void* arg) {
    sem_wait(&sem_c_d);
    z = v * x6;
    printf("Calulated z = %d (d)\n", z);
}

void* thread_cal_e(void* arg) {
    sem_wait(&sem_e);
    sem_wait(&sem_e);
    y = w * y;
    printf("Calulated y = %d (e)\n", y);
    sem_post(&sem_g);
}

void* thread_cal_f(void* arg) {
    z = w * z;
    printf("Calulated z = %d (f)\n", z);
    sem_post(&sem_g);
}

void* thread_cal_g(void* arg) {
    sem_wait(&sem_g);
    sem_wait(&sem_g);
    ans = y + z;
    printf("Calulated ans = %d (g)\n", ans);
}

int main() {
    pthread_t threadA, threadB, threadC, threadD, threadE, threadF, threadG;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem_c_d, 0, 0);
    sem_init(&sem_e, 0, 0);
    sem_init(&sem_g, 0, 0);

    pthread_create(&threadA, NULL, thread_cal_a, NULL);
    pthread_create(&threadB, NULL, thread_cal_b, NULL);
    pthread_create(&threadC, NULL, thread_cal_c, NULL);
    pthread_create(&threadD, NULL, thread_cal_d, NULL);
    pthread_create(&threadE, NULL, thread_cal_e, NULL);
    pthread_create(&threadF, NULL, thread_cal_f, NULL);
    pthread_create(&threadG, NULL, thread_cal_g, NULL);

    sleep(3);
    sem_destroy(&sem_c_d);
    sem_destroy(&sem_e);
    sem_destroy(&sem_g);
    pthread_mutex_destroy(&mutex);
    return 0;
}