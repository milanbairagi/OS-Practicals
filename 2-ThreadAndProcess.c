#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function to be run by the thread
void* threadFunction(void* arg) {
    printf("Hello from Thread! Thread ID: %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;

    // Create a thread
    if (pthread_create(&thread_id, NULL, threadFunction, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for thread to finish
    pthread_join(thread_id, NULL);

    printf("Thread execution complete.\n");

    // Create a new process using fork()
    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork process");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello from Child Process! PID: %d\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Hello from Parent Process! PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
