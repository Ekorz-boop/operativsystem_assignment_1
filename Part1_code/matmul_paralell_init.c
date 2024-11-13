/***************************************************************************
 *
 * Paralell version of matrix-matrix multiplication time: between 0.5 and 1 second
 * Paralell version of matrix-matrix multiplication with paralell initialization time:  less than 0.5 seconds 
 * (got 0 seconds since time resolution is 1 second)
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

Task 14 additon: Parallelize the initialization of the matrices also, i.e., the function init_matrix. Use one thread to initialize each of the
rows in the matrices a and b. Compile, link, and execute your program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 1024

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

typedef struct {
    int mul_row_index;
} threadArgs_mul;

typedef struct {
    int init_row_index;
} threadArgs_init;


threadArgs_mul multiplicaton_args[SIZE]; // Array of arguments for each thread (size big since we have one thread per row)
threadArgs_init initialization_args[SIZE]; // Array of arguments for each thread (size big since we have one thread per row)
pthread_t thread_array_mul[SIZE]; // Array of threads (size big since we have one thread per row)
pthread_t thread_array_init[SIZE]; // Array of threads (size big since we have one thread per row)


void *mat_init_thread(void *args) {
    threadArgs_init *thread_args = (threadArgs_init*)args;

    // Grab the row (i) to initialize which is fixed for this thread
    int i = thread_args->init_row_index;
    // Same calculation as before but only for this i (since it's paralellized)
    // i is the row number (which is fixed for this thread)
    // j is the column number (which will be iterated over to fill the entire row)
    for (int j = 0; j < SIZE; j++) {
        a[i][j] = 1.0;
        b[i][j] = 1.0;
    }
}


static void init_matrix_paralell() {
    // Create thread for each row to be initialized
    for (int i = 0; i < SIZE; i++) {
        initialization_args[i].init_row_index = i;
        pthread_create(&thread_array_init[i], NULL, mat_init_thread, (void*)&initialization_args[i]);
    }

    // Wait for all threads to finish using join
    for (int i = 0; i < SIZE; i++) {
        pthread_join(thread_array_init[i], NULL);
    }
}


void *matmul_thread(void *args) {
    threadArgs_mul *thread_args = (threadArgs_mul*)args;

    // Grab the row (i) which is fixed for this thread
    int i = thread_args->mul_row_index;

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
        multiplicaton_args[i].mul_row_index = i;
        pthread_create(&thread_array_mul[i], NULL, matmul_thread, (void*)&multiplicaton_args[i]);
    }

    // Wait for all threads to finish using join
    for (int i = 0; i < SIZE; i++) {
        pthread_join(thread_array_mul[i], NULL);
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
    time_t start, end;
    start = time(NULL);
    init_matrix_paralell();
    matmul_paralell();
    end = time(NULL);
    printf("Time taken: %ld\n", end - start);
    //print_matrix();
}
