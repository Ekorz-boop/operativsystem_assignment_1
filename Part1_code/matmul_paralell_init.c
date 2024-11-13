/***************************************************************************
 *
 * Paralell version of matrix-matrix multiplication time:
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

#define SIZE 1024

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

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

static void
matmul_seq()
{
    int i, j, k;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            c[i][j] = 0.0;
            for (k = 0; k < SIZE; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
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
    matmul_seq();
    //print_matrix();
}
