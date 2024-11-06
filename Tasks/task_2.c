#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSIZE 128
#define SHM_R 0400
#define SHM_W 0200

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
		int buffer;
		unsigned empty;
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
	pid = fork();
	if (pid != 0) {
		/* here's the parent, acting as producer */
		while (var1 < 100) {
			/* write to shmem */
			var1++;
			while (shmp->empty == 1); /* busy wait until the buffer is empty */
			printf("Sending %d\n", var1); fflush(stdout);
			shmp->buffer = var1;
			shmp->empty = 1;
		}
		shmdt(addr);
		shmctl(shmid, IPC_RMID, shm_buf);
	} else {
		/* here's the child, acting as consumer */
		while (var2 < 100) {
			/* read from shmem */
			while (shmp->empty == 0); /* busy wait until there is something */
			var2 = shmp->buffer;
			shmp->empty = 0;
			printf("Received %d\n", var2); fflush(stdout);
		}
		shmdt(addr);
		shmctl(shmid, IPC_RMID, shm_buf);
	}
}
