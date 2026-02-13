#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5
#define ITERATIONS 100000

int counter = 0;
sem_t mutex;

void* unsynchronized_increment(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        int temp = counter;
        temp = temp + 1;
        counter = temp;
    }
    return NULL;
}

void* synchronized_increment(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(&mutex);
        int temp = counter;
        temp = temp + 1;
        counter = temp;
        sem_post(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("--- Critical Section Problem ---\n");
    
    printf("\n1. Without Synchronization (Race Condition):\n");
    counter = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, unsynchronized_increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Expected Counter: %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual Counter:   %d\n", counter);

    printf("\n2. With Semaphore Synchronization:\n");
    counter = 0;
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, synchronized_increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Expected Counter: %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual Counter:   %d\n", counter);
    sem_destroy(&mutex);

    return 0;
}
