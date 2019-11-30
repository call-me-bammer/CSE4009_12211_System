#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void sigint_handler(int sig);

int main(int argc, char** argv) {

    int stat;
    pid_t pid;
    printf("starting...\n");

    //signal(SIGINT, sigint_handler);

    if ((pid = fork()) == 0) {
        while (1) {
            printf("hello world\n");
            sleep(1);
        }
    }
    else {
        kill(pid, SIGINT);
        waitpid(pid, &stat, 0);
        if (WIFSIGNALED(stat)) {
            psignal(WTERMSIG(stat), "Child term due to");
        }
    }

    return 0;
}

void sigint_handler(int sig) {
    printf("Caught signal %d\n", sig);
    fflush(stdout);
}