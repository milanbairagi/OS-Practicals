// File: dining_philosophers.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5  // Number of philosophers

// States
#define THINKING 0
#define HUNGRY   1
#define EATING   2

int state[N];
 
// Simple semaphore
typedef struct {
    int value;
} semaphore;

// Custom semaphore functions
void wait(semaphore *s) {
    while (s->value <= 0);
    s->value--;
}

void signal(semaphore *s) {
    s->value++;
}

// Declare semaphores
semaphore mutex = {1};
semaphore s[N];  // One for each philosopher

pthread_t threads[N];

// Function to display state
void print_states() {
    char* states[] = {"THINKING", "HUNGRY", "EATING"};
    for (int i = 0; i < N; i++) {
        printf("Philosopher %d is %s\n", i, states[state[i]]);
    }
    printf("-----------------------------\n");
}

// Check if philosopher can eat
void test(int i) {
    int left = (i + N - 1) % N;
    int right = (i + 1) % N;

    if (state[i] == HUNGRY && state[left] != EATING && state[right] != EATING) {
        state[i] = EATING;
        signal(&s[i]);
    }
}

void take_chopsticks(int i) {
    wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);
    test(i);
    signal(&mutex);
    wait(&s[i]);  // Wait if not allowed to eat yet
}

void put_chopsticks(int i) {
    wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down chopsticks\n");
    test((i + N - 1) % N);  // Test left neighbor
    test((i + 1) % N);      // Test right neighbor
    signal(&mutex);
}

void* philosopher(void* num) {
    int i = *(int*)num;
    while (1) {
        sleep(1); // Thinking
        take_chopsticks(i);
        printf("Philosopher %d is EATING\n", i);
        sleep(2); // Eating
        put_chopsticks(i);
    }
}

int main() {
    int i;
    int indices[N];

    for (i = 0; i < N; i++) {
        s[i].value = 0;
        state[i] = THINKING;
        indices[i] = i;
    }

    for (i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &indices[i]);
    }

    // Let them dine for a while
    sleep(10);

    return 0;
}
