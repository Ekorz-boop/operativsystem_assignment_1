#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#define SHMSIZE 128
#define SHM_R 0400
#define SHM_W 0200
#define BUFFER_SIZE 10

/*  
Modify the program in Listing 2 (shmem.c) so the buffer contains 10 numbers instead of only one number. Implement it
as a circular, bounded buffer, i.e.,
• the items shall be fetched by the consumer in the same order at they were put into the buffer by the producer,
• when you come to the end of the buffer you start over from the first buffer place, and
• it is not allowed to fill the buffer with 10 items before the consumer runs / fetches items in the buffer.
The producer, i.e., the parent process, shall wait a random time between 0.1s - 0.5s each time it has put a number into the
buffer. Similarly, the consumer, i.e., the child process, shall also wait a random time between 0.2s - 2s each time it has
fetched a number from the buffer.
Comment your program and explain where and how the problems described above can occur.
*/

int main(int argc, char **argv)
{
	struct shm_struct {
		int buffer[BUFFER_SIZE]; // Turned buffer into an array of size 10
		unsigned empty;
		int in; // Keeps track of how many items inserted to buffer
		int out; // Keeps track of many items removed from buffer
	};
	volatile struct shm_struct *shmp = NULL;
	char *addr = NULL;
	pid_t pid = -1;
	int var1 = 0, var2 = 0, shmid = -1;
	struct shmid_ds *shm_buf;

	/* allocate a chunk of shared memory */
	shmid = shmget(IPC_PRIVATE, SHMSIZE, IPC_CREAT | SHM_R | SHM_W);
	shmp = (struct shm_struct *) shmat(shmid, addr, 0);
	shmp->empty = 0;
	shmp->in = 0;
	shmp->out = 0;
	pid = fork();
	if (pid != 0) {
		srand(time(NULL)); // set a random seed.
		/* here's the parent, acting as producer */
		while (var1 < 100) {
			/* write to shmem */
			var1++;
			while (shmp->empty == 1); /* busy wait until the buffer is empty */
			printf("Sending %d\n", var1); fflush(stdout);
			shmp->buffer[shmp->in] = var1; // Insert var1 to buffer with index of in
			usleep((rand() % 400 + 100) * 1000); // Sleep between 0.1s and 0.5s
			shmp->in++; //increment in
			// If we have 10 items in the buffer then set empty to 1
	 		if (shmp->in == 10){
				shmp->empty = 1;
			}
		}
		shmdt(addr);
		shmctl(shmid, IPC_RMID, shm_buf);
	} else {
		srand(time(NULL) + 1); // set a different random seed.
		/* here's the child, acting as consumer */
		while (var2 < 100) {
			/* read from shmem */
			while (shmp->empty == 0); /* busy wait until there is something */
			var2 = shmp->buffer[shmp->out];	 // set var2 to be the same as buffer on index out
			usleep((rand() % 1800 + 200) * 1000);  // Sleep between 0.2s and 2s
			shmp->out++; //increment out
			// If 10 items have been removed then reset the index variables and set empty to 0
			if(shmp->out == shmp->in){
				shmp->in = 0;
				shmp->out = 0;
				shmp->empty = 0;
			}
			printf("Received %d\n", var2); fflush(stdout);
		}
		shmdt(addr);
		shmctl(shmid, IPC_RMID, shm_buf);
	}
}
