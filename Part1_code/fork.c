#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid;
    unsigned i;
    unsigned niterations = 100;
    pid = fork();
    if (pid == 0) {
        for (i = 0; i < niterations; ++i)
            printf("A = %d, ", i);
            printf("In child => Own pid : %d\n", getpid());
            printf("In child => Parent's pid : %d\n", pid);
     } else {
        for (i = 0; i < niterations; ++i)
            printf("B = %d, ", i);
            printf("In child => Own pid : %d\n", getpid());
            printf("In child => Parent's pid : %d\n", pid);
    }
    printf("\n");
    
    // }
    // else{
    //   printf("In Parent => Child's pid is %d\n", pid);
}
