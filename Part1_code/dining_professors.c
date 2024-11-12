#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/*
Implement Dining Professors with five professors according to the description above. The program shall contain five
threads, where each thread represents one professor. The program must guarantee that only one professor at the time can
use a chopstick.
• Let the professors think a random time between one and five seconds.
• Take the left chopstick.
• When they have gotten the left chopstick, let them think in two to eight seconds.
• Take the right chopstick.
• Let the professor eat for a random time between five-ten seconds, and then put down both chopsticks.
• Write information to the terminal when the professors go from one state to another, e.g., "Tanenbaum: thinking ->
got left chopstick". Also indicate when a professor tries to take a chopstick.
There are some restrictions for your implementation.
• Each fork should be modeled as a shared resource, which exclusive usage.
• You are not allowed to look at the state of your neighbors to see if they are eating or not, i.e., the solution in Section
2.5.1 in the course book [2] is not allowed.
*/

// Defines
#define num_dudes 5 // Define since we need to use this value several times

// Global vars
pthread_mutex_t *chopstick_mutexes;
pthread_t *philosopher_threads;

// Struct for thread args
typedef struct {
    pthread_mutex_t left_stick;
    pthread_mutex_t right_stick;
    char *philosopher_name;
} threadArgs;

// Functions
void* philosopher_thread(void *args) {
    threadArgs *philosopher = (threadArgs*)args; 
    for (int cycle = 0; cycle < 5; cycle++) { // Do stuff in cycles so they dont just try everything once
        printf("%s is THINKING\n", philosopher->philosopher_name);
        sleep(rand() % (5 + 1)); // Waiting timer. format: rand() % (upper_bound + lower_bound)
        printf("%s will try to grab LEFT chopstick\n", philosopher->philosopher_name);

        // Lock the left stick (i.e. it's taken)
        pthread_mutex_lock(&philosopher->left_stick);

        printf("%s got the LEFT chopstick\n", philosopher->philosopher_name); // Can only reach here if it actually got it since lock
        sleep(rand() % (8 + 2)); // Waiting timer. format: rand() % (upper_bound + lower_bound)
        printf("%s will try to grab RIGHT chopstick\n", philosopher->philosopher_name);

        // Lock the right stick (i.e. it's taken)
        pthread_mutex_lock(&philosopher->right_stick);

        printf("%s got the RIGHT chopstick\n", philosopher->philosopher_name); // Can only reach here if it actually got it since lock
        printf("%s got BOTH chopsticks, is now EATING\n", philosopher->philosopher_name);
        sleep(rand() % (10 + 5)); // Waiting timer. format: rand() % (upper_bound + lower_bound)

        // Unlock both sticks (i.e. release them)
        pthread_mutex_unlock(&philosopher->left_stick);
        pthread_mutex_unlock(&philosopher->right_stick);

        printf("%s RELEASED both chopsticks\n", philosopher->philosopher_name); // Can only reach here if it actually had both and unlocked them since locks
    }
}

int main() {
    char *philosopher_names[] = {"Tanenbaum", "Bos", "Lamport", "Stallings", "Silberschatz"};
    // Create and alloc mem for the philosopher threads
    philosopher_threads = malloc(num_dudes * sizeof(pthread_t));
    // Create and alloc mem for the args/struct
    threadArgs *thread_args = malloc(num_dudes * sizeof(threadArgs));
    // Create and alloc mem for the mutexes
    chopstick_mutexes = malloc(num_dudes * sizeof(pthread_mutex_t));

    // Go through and initialize all the mutexes
    for (int i = 0; i < num_dudes; i++) {
        pthread_mutex_init(&chopstick_mutexes[i], NULL);
    }

    // Go through and initialize args for each philosopher
    for (int i = 0; i < num_dudes; i++) {
        // Provide the sticks mutexes to the philosopher
        thread_args[i].left_stick = chopstick_mutexes[i];
		thread_args[i].right_stick = chopstick_mutexes[(i + 1) % num_dudes];
        // Provide the name for the philosopher
        thread_args[i].philosopher_name = philosopher_names[i];
    }

    // Go through and start the threads for each philosopher
    for (int i = 0; i < num_dudes; i++) {
        pthread_create(&philosopher_threads[i], NULL, philosopher_thread, &thread_args[i]);
    }

    // Join the threads when they are finished to terminate them
    for (int i = 0; i < num_dudes; i++) {
        pthread_join(philosopher_threads[i], NULL);
    }

    // Destroy all the mutexes to avoid memory leaks
    for (int i = 0; i < num_dudes; i++) {
        pthread_mutex_destroy(&chopstick_mutexes[i]);
    }

    // Free all the malloced stuff to avoid memory leak
    free(chopstick_mutexes);
    free(thread_args);
    free(philosopher_threads);
}

