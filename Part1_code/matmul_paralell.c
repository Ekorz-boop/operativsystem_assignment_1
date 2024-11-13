/***************************************************************************
 *
 * Paralell version of matrix-matrix multiplication time: less than 1 second
 *
 ***************************************************************************/
/*
We will now parallelize the matrix multiplication program using threads. Parallelize the program according to the following
assumptions:
• Parallelize only the matrix multiplication, but not the initialization.
• A new thread shall be created for each row to be calculated in the matrix.
• The row number of the row that a thread shall calculate, shall be passed to the new thread as a parameter to the new
thread.
• The main function shall wait until all threads have terminated before the program terminates.
Compile and link your parallel version of the matrix multiplication program. Don’t forget to add -lpthread when you
link your program. We will now measure how much faster the parallel program is as compared to the sequential one.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

typedef struct {
    int i;
} threadArgs;

threadArgs multiplicaton_args[SIZE]; // Array of arguments for each thread
pthread_t thread_array[SIZE]; // Array of threads

static void
init_matrix(void)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
	        /* Simple initialization, which enables us to easy check
	         * the correct answer. Each element in c will have the same
	         * value as SIZE after the matmul operation.
	         */
	        a[i][j] = 1.0;
	        b[i][j] = 1.0;
        }
}


void *matmul_thread(void *args) {
    threadArgs *thread_args = (threadArgs*)args;

    // Grab the row
    int i = thread_args->i;

    // Same calculation as before but only for this i (since it's paralellized)
    for (int j = 0; j < SIZE; j++) {
        c[i][j] = 0.0;
        for (int k = 0; k < SIZE; k++)
            c[i][j] = c[i][j] + a[i][k] * b[k][j];
    }
}


static void matmul_paralell() {
    // Create thread for each row
    for (int i = 0; i < SIZE; i++) {
        multiplicaton_args[i].i = i;
        pthread_create(&thread_array[i], NULL, matmul_thread, (void*)&multiplicaton_args[i]);
    }

    // Wait for all threads to finish using join
    for (int i = 0; i < SIZE; i++) {
        pthread_join(thread_array[i], NULL);
    }
}


static void
print_matrix(void)
{
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++)
	        printf(" %7.2f", c[i][j]);
	        printf("\n");
    }
}


int
main(int argc, char **argv)
{
    init_matrix();
    matmul_paralell();
    //print_matrix();
}
