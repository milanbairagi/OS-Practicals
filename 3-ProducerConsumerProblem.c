#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 5
int buffer[SIZE];
int in = 0, out = 0;

// Simple Semaphore structure
typedef struct {
    int value;
} semaphore;

// Custom semaphore functions
void wait(semaphore *s) {
    while (s->value <= 0); // Busy wait
    s->value--;
}

void signal(semaphore *s) {
    s->value++;
}

// Semaphores
semaphore empty = {SIZE};
semaphore full = {0};
semaphore mutex = {1};

// Producer function
void* producer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        wait(&empty);
        wait(&mutex);

        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % SIZE;

        signal(&mutex);
        signal(&full);

        sleep(1); // Simulate production time
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        wait(&full);
        wait(&mutex);

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        signal(&mutex);
        signal(&empty);

        sleep(1); // Simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
