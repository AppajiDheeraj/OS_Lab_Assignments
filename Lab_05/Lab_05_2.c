#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_data = 0;
int read_count = 0;
sem_t mutex, wrt;

void* unsynchronized_reader(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 3; i++) {
        printf("Reader %d reading: %d\n", id, shared_data);
        usleep(100000);
    }
    return NULL;
}

void* unsynchronized_writer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 3; i++) {
        shared_data++;
        printf("Writer %d writing: %d\n", id, shared_data);
        usleep(150000);
    }
    return NULL;
}

void* synchronized_reader(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 3; i++) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %d reading: %d\n", id, shared_data);
        usleep(100000);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) sem_post(&wrt);
        sem_post(&mutex);
        usleep(50000);
    }
    return NULL;
}

void* synchronized_writer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 3; i++) {
        sem_wait(&wrt);
        shared_data++;
        printf("Writer %d writing: %d\n", id, shared_data);
        usleep(150000);
        sem_post(&wrt);
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t r_threads[NUM_READERS], w_threads[NUM_WRITERS];
    int r_ids[NUM_READERS], w_ids[NUM_WRITERS];

    printf("--- Readers-Writers Problem ---\n");

    printf("\n1. Without Synchronization (Race Condition possible):\n");
    shared_data = 0;
    for (int i = 0; i < NUM_READERS; i++) {
        r_ids[i] = i + 1;
        pthread_create(&r_threads[i], NULL, unsynchronized_reader, &r_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        w_ids[i] = i + 1;
        pthread_create(&w_threads[i], NULL, unsynchronized_writer, &w_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) pthread_join(r_threads[i], NULL);
    for (int i = 0; i < NUM_WRITERS; i++) pthread_join(w_threads[i], NULL);

    printf("\n2. With Semaphore Synchronization:\n");
    shared_data = 0;
    read_count = 0;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&r_threads[i], NULL, synchronized_reader, &r_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&w_threads[i], NULL, synchronized_writer, &w_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) pthread_join(r_threads[i], NULL);
    for (int i = 0; i < NUM_WRITERS; i++) pthread_join(w_threads[i], NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
