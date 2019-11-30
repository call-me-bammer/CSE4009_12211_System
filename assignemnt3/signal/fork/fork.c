#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

/* Global variables */
extern char **environ;      /* defined in libc */

int main(int argc, char** argv) {

    volatile sig_atomic_t pid;

    if ((pid = fork()) == 0) {
        exit(0);
    }
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", pid);


    return 0;
}