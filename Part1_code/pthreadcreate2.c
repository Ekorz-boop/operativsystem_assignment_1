#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
Creating a unique struct threadArgs instance for each thread ensures that each thread has its own independent copy of the data it needs.
Avoiding Data Race Conditions: If all threads shared a single threadArgs struct, they would each overwrite the values of id, numThreads, and squaredId.
Passing Data Between Threads: Each thread needs to know its unique id and store its calculated squaredId independently.
Dynamic Allocation for Flexibility: When you dynamically allocate an array of threadArgs, it’s easy to create a variable number of threads
*/


struct threadArgs {
	unsigned int id;
	unsigned int numThreads;
};

void* child(void* params) {
	struct threadArgs *args = (struct threadArgs*) params;
	unsigned int childID = args->id;
	unsigned int numThreads = args->numThreads;
	printf("Greetings from child #%u of %u\n", childID, numThreads);
	free(args);
}

int main(int argc, char** argv) {
	pthread_t* children; // dynamic array of child threads
	struct threadArgs* args; // argument buffer
	unsigned int numThreads = 0;
	// get desired # of threads
	if (argc > 1)
		numThreads = atoi(argv[1]);
	children = malloc(numThreads * sizeof(pthread_t)); // allocate array of handles
	for (unsigned int id = 0; id < numThreads; id++) {
		// create threads
		args = malloc(sizeof(struct threadArgs));
		args->id = id;
		args->numThreads = numThreads;
		pthread_create(&(children[id]), // our handle for the child
			NULL, // attributes of the child
			child, // the function it should run
			(void*)args); // args to that function
	}
	printf("I am the parent (main) thread.\n");
	for (unsigned int id = 0; id < numThreads; id++) {
		pthread_join(children[id], NULL );
	}
	free(children); // deallocate array
	return 0;
}
