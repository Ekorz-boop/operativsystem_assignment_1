#include <stdio.h>
#include <stdlib.h>
/* test1.c */

#define SIZE (32*1024)
#define ITERATIONS 10

int main(int argc, char **argv)
{
    struct link {
        int x[SIZE][SIZE];
    };
    struct link *start;
    int iteration, i, j;
    start = (struct link *) calloc(1, sizeof(struct link));
    if (!start) {
        printf("Fatal error: Can't allocate memory of %d x %d = %lu\n", SIZE, SIZE, (unsigned long)SIZE*SIZE);
        exit(-1);
    }
    for (iteration = 0; iteration < ITERATIONS; iteration++) {
        printf("test1, iteration: %d\n", iteration);
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                start->x[i][j] = 0;
    }
}
