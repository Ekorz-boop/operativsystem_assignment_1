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
#define num_dudes 5

// Global vars
pthread_mutex_t *global_chopsticks_locks;
pthread_t *philosopher_threads;

// Struct for thread args
struct threadArgs {
    pthread_mutex_t left_stick;
    pthread_mutex_t right_stick;
    char *philosopher_name;
} threadArgs;

// Functions
void* philosopher_thread(void *args) {
    threadArgs *philosopher = (struct threadArgs *)args; 
    for (int cycle = 0; cycle < 20; cycle++) { // Do stuff in cycles so they dont just try everything once
        printf("%s is THINKING\n", philosopher->philosopher_name);
        sleep(rand() % (5 + 1)); // Waiting timer. format: rand() % (upper_bound + lower_bound)
        printf("%s will try to grab LEFT chopstick", philosopher->philosopher_name);
        // ADD HERE: lock left stick
        printf("%s got the LEFT chopstick", philosopher->philosopher_name); // Can only reach here if it actually got it since lock
        sleep(rand() % (8 + 2)); // Waiting timer. format: rand() % (upper_bound + lower_bound)
        printf("%s will try to grab RIGHT chopstick", philosopher->philosopher_name);
        // ADD HERE: lock roght stick
        printf("%s got the RIGHT chopstick", philosopher->philosopher_name); // Can only reach here if it actually got it since lock
        printf("%s got BOTH chopsticks, is now EATING", philosopher->philosopher_name);
        sleep(rand() % (10 + 5)); // Waiting timer. format: rand() % (upper_bound + lower_bound)
        // ADD HERE: unlock left stick
        // ADD HERE: unlock right stick
        printf("%s RELEASED both chopsticks", philosopher->philosopher_name); // Can only reach here if it actually had both and unlocked them since locks
    }
}

int main() {
    char *philosopher_names[] = {"Tanenbaum", "Bos", "Lamport", "Stallings", "Silberschatz"};
}

