#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];

void* unsynchronized_philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < 2; i++) {
        printf("Philosopher %d is thinking\n", id);
        // No real synchronization, just simulation of picking up
        printf("Philosopher %d picked up chopstick %d and %d\n", id, left, right);
        printf("Philosopher %d is eating\n", id);
        usleep(100000);
        printf("Philosopher %d put down chopstick %d and %d\n", id, left, right);
    }
    return NULL;
}

void* synchronized_philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < 2; i++) {
        printf("Philosopher %d is thinking\n", id);
        
        if (id % 2 == 0) {
            sem_wait(&chopsticks[right]);
            sem_wait(&chopsticks[left]);
        } else {
            sem_wait(&chopsticks[left]);
            sem_wait(&chopsticks[right]);
        }

        printf("Philosopher %d is eating\n", id);
        usleep(100000);

        sem_post(&chopsticks[left]);
        sem_post(&chopsticks[right]);
        printf("Philosopher %d finished eating\n", id);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    printf("--- Dining Philosophers Problem ---\n");

    printf("\n1. Without Synchronization (Conceptual simulation of race/overlap):\n");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, unsynchronized_philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) pthread_join(threads[i], NULL);

    printf("\n2. With Semaphore Synchronization (Deadlock avoidance via ordering):\n");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) sem_init(&chopsticks[i], 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, synchronized_philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) pthread_join(threads[i], NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) sem_destroy(&chopsticks[i]);

    return 0;
}
