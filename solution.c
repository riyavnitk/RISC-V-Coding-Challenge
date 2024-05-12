#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>

#define SHM_KEY 1234            // Shared memory key
#define SHM_SIZE 1024           // Shared memory size

volatile sig_atomic_t flag = 0; // Flag to indicate if SIGINT is received
int *shared_counter;            // Shared counter

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for shared counter

// Increment thread that increments the shared counter
void *thread_increment(void *arg) {
    while (!flag) { 
        pthread_mutex_lock(&mutex); 
        (*shared_counter)++; 
        printf("Increment Thread: Counter = %d\n", *shared_counter); 
        pthread_mutex_unlock(&mutex); 
        sleep(1);
    }
    pthread_exit(NULL);
}

// Decrement thread that decrements the shared counter
void *thread_decrement(void *arg) {
    while (!flag) {
        pthread_mutex_lock(&mutex);
        (*shared_counter)--;
        printf("Decrement Thread: Counter = %d\n", *shared_counter);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

// Signal handler for SIGINT
void signal_handler(int sig) {
    if (sig == SIGINT) {
        flag = 1;
        printf("\nSIGINT received. Exiting...\n");
    }
}

// Main function
int main() {
    // Register signal handler
    signal(SIGINT, signal_handler);

    // Create shared memory segment
    int shmid; // Shared memory ID
    if ((shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shared_counter = (int *)shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    *shared_counter = 0;

    // Create threads
    pthread_t increment_thread, decrement_thread;
    if (pthread_create(&increment_thread, NULL, thread_increment, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    if (pthread_create(&decrement_thread, NULL, thread_decrement, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    // Wait for threads to finish
    pthread_join(increment_thread, NULL);
    pthread_join(decrement_thread, NULL);

    // Detach and remove shared memory
    shmdt(shared_counter);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
