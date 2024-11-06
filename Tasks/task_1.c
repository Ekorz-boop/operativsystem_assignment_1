#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid;
    pid_t pid2;
    unsigned i;
    unsigned niterations = 1;
    pid = fork();
    if (pid == 0) {
        // Is the first love child. UwU
        for (i = 0; i < niterations; ++i) {
            printf("A = %d, ", i);
            printf("\n");
        }
        printf("In child (A) => Own pid : %d\n", getpid());
        // printf("In child => Parent's pid : %d\n", pid);
    } 
    else 
    {   
        pid2 = fork();
        if (pid2 == 0) {
            // Catches the child from the second fork
            for (i = 0; i < niterations; ++i) {
                    printf("B = %d, ", i);
                    printf("\n");
                }
                printf("In child (B) => Own pid : %d\n", getpid());
                // printf("In child => Parent's pid : %d\n", pid2);
        }
        else {
            // Catches original parent process
            for (i = 0; i < niterations; ++i) {
                    printf("C = %d, ", i);
                    printf("\n");
                }
                printf("\n");
                printf("In Parent (C) => Own pid : %d\n", getpid());
                printf("In Parent (C) => First Child pid is %d\n", pid);
                printf("In Parent (C) => Second Child pid is %d\n", pid2);
            }
    }
}