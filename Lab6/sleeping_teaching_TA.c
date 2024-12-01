#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

// Sleeping Teaching Teacher Assistance

// This code will implement:
// Use pthreads, create n students, each student is a thread
// Teacher Assistance is a thread too
// Student will alternate between programming and seeking help from TA
// If student finds TA sleeping, student must wakes TA with a semaphore
// Simulating student programming and TA providing help to student by making that thread sleep for a period of time.

#define WAITING_CHAIRS 3

int n; // The number of students
sem_t semTA; // Semaphore to wake up the TA
sem_t semStudent; // Semaphore for students getting help
pthread_mutex_t mutex;
int n_waiting = 0; // Number of students waiting in chairs
int chairs[WAITING_CHAIRS] = {-1, -1, -1}; // Queue for waiting students
bool TA_nap = false;
bool TA_exit = false;

typedef struct student_arg {
    int id;
} student_arg;

//function for student thread
void *student(void *arg) {
    student_arg *sargs = (student_arg *)arg;
    int id = sargs->id;

//student will alternate between programming and seeking help
    while (true) {
        printf("Student %d is programming\n", id);
        int programming_time = rand() % 7 + 1;
        sleep(programming_time);

        printf("Student %d is going to seek help from TA\n", id);

        pthread_mutex_lock(&mutex);
        if (n_waiting < WAITING_CHAIRS) {
            chairs[n_waiting] = id; // Add student to the queue
            n_waiting++;
            printf("Student %d is waiting. Waiting students: %d\n", id, n_waiting);

            if (TA_nap) {
                TA_nap = false;
                printf("Student %d wakes up the TA\n", id);
                sem_post(&semTA); // Wake up the TA
            }
            pthread_mutex_unlock(&mutex);

            sem_wait(&semStudent); // Wait for TA's help
            printf("Student %d got help and returning to programming\n", id);
        } else {
            printf("Student %d found no available chairs and will try later\n", id);
            pthread_mutex_unlock(&mutex);
        }
    }
}

void *teacher_assistance(void *arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        if (n_waiting == 0) {
            printf("No students waiting, TA is napping\n");
            TA_nap = true;
            pthread_mutex_unlock(&mutex);
            sem_wait(&semTA); // Wait until a student wakes the TA
        } else {
            int student_id = chairs[0]; // Get the first student in the queue
            for (int i = 0; i < n_waiting - 1; i++) {
                chairs[i] = chairs[i + 1]; // Shift the queue
            }
            n_waiting--;
            pthread_mutex_unlock(&mutex);

            int help_time = rand() % 5 + 1;
            printf("TA is going to help student %d for %d seconds\n", student_id, help_time);
            sleep(help_time);
            sem_post(&semStudent); // Signal that the student got help
        }

        if (TA_exit) {
            printf("Its the end of office hours, TA is going home\n");
            pthread_exit(NULL);
        }
    }
}

int main() {
    printf("Input the number of students: ");
    scanf("%d", &n);

    pthread_t TA;
    pthread_t students[n];
    student_arg students_arg[n];

//initialize random seed, semaphore and mutex lock
    srand(time(NULL));
    sem_init(&semTA, 0, 0);
    sem_init(&semStudent, 0, 0);
    pthread_mutex_init(&mutex, NULL);

//create TA and student thread
    pthread_create(&TA, NULL, teacher_assistance, NULL);
    for (int i = 0; i < n; i++) {
        students_arg[i].id = i + 1;
        pthread_create(&students[i], NULL, student, &students_arg[i]);
    }

    sleep(20); // simulate office hours, after this TA will finish teaching the last student and go home.
    TA_exit = true;

    pthread_join(TA, NULL);

    for (int i = 0; i < n; i++) {
        printf("Student %d is going home\n", i+1);
        pthread_cancel(students[i]);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semTA);
    sem_destroy(&semStudent);

    printf("Office hours are over\n");
    return 0;
}

