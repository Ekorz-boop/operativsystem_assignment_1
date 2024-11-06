#include <stdio.h>
#include <unistd.h>

/*
Compile and execute the program in fork.c (see Listing 1).
Which process is the parent and which is the child process?
The variable i is used in both processes. Is the value of i in one process affected when the other process increments
it? Why/Why not?
Modify the program in two ways:
• Let the program create a third process, that writes 100 "C" (similarly to "A" and "B")
• In the parent process, print out the process id (pid) of each of the child processes. It is not allowed to use getpid()
to get the process id of the child processes.
Which are the process identities (pid) of the child processes?
*/

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