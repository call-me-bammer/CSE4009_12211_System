#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* 
 * Child status information
 *
 * reported by wait
 *
 * - normal / abnormal termination
 * - termination cause
 * - exit status
 *
 * WIF ... macros (param: int status)
 * 1.  WIFEXITED():     child exited normally
 *  => WEXITSTATUS():   return code when child exits
 *
 * 2.  WIFSIGNALED():   child exited because a signal was not caught
 *  => WTERMSIG():      gives the number of the termination signal
 *
 * 3.  WIFSTOPPED():    child is stopped
 *  => WSTOPSIG():      gives the number of the stop signal
 */

void waitexample() {
    int stat;

    // This status 2 is reported by WEXITSTATUS
    if (fork() == 0) {
        exit(2);
    }
    else {
        wait(&stat);
    }

    if (WIFEXITED(stat)) {
        printf("Exit status: %d\n", WEXITSTATUS(stat));
    }
    else if (WIFSIGNALED(stat)) {
        /* if we want to prints information about a signal */
        psignal(WTERMSIG(stat), "Exit signal");
    }
}

int main() {
    waitexample();
    return 0;
}