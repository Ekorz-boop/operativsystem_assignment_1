#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/* 
In Listing 8 (pthreadcreate3.c), we provide a program where the parent thread allocates (and deallocates) an array
of structs of type threadArgs, one struct for each child thread. The threadArgs struct passed to each child
thread should also be used to pass values from the child thread to the parent thread.
Your task is to:
• Add a new variable in the struct threadArgs, called squaredId. [DONE]
• In the child thread, take the thread id, square it, and return the value. Use the threadArgs struct for communicating
values between the parent and the child. [DONE]
• In the main program, wait for all child threads to terminate, and then print the squared id for each thread (this value
should be sent to the parent thread by each child thread). [DONE]
*/


struct threadArgs {
	unsigned int id;
	unsigned int numThreads;
	unsigned int squaredId; // New squaredId for storing the ID
};

void* child(void* params) {
	struct threadArgs *args = (struct threadArgs*) params;
	unsigned int childID = args->id;
	unsigned int numThreads = args->numThreads;
	// Set the squaredId to the square of the id (in this case we simply multuiply it with itself instead of using squared operator)
	args->squaredId = childID * childID; 
	printf("Greetings from child #%u of %u\n", childID, numThreads);
	return NULL;
}

int main(int argc, char** argv) {
	pthread_t* children; // dynamic array of child threads
	struct threadArgs* args; // argument buffer
	unsigned int numThreads = 0;
	// get desired # of threads
	if (argc > 1)
		numThreads = atoi(argv[1]);
	children = malloc(numThreads * sizeof(pthread_t)); // allocate array of handles
	args = malloc(numThreads * sizeof(struct threadArgs)); // args vector
	for (unsigned int id = 0; id < numThreads; id++) {
		// create threads
		args[id].id = id;
		args[id].numThreads = numThreads;
		pthread_create(&(children[id]), // our handle for the child
			NULL, // attributes of the child
			child, // the function it should run
			(void*)&args[id]); // args to that function
	}
	printf("I am the parent (main) thread.\n");
	for (unsigned int id = 0; id < numThreads; id++) {
		pthread_join(children[id], NULL );
	}
	// This is after each thread is joined (terminated) so here we will loop through all threadArgs and print their id and squaredId
	for (unsigned int i = 0; i < numThreads; i++) {
		printf("Normal id: %d, Squared id: %d\n", args[i].id, args[i].squaredId);
	}

	free(args); // deallocate args vector
	free(children); // deallocate array
	return 0;
}
