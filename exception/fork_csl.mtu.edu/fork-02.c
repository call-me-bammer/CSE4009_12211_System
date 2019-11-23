#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/* why MAX_COUNT and use printf?
 * 
 * CPU scheduler will assign a time quantum to each process
 * so a process will run for some time before the control is switched to the other
 * 
 * therefore MAX_COUNT should be large enough so that
 * both processes will run for at least two or more time quanta.
 */
#define MAX_COUNT 200
void ChildProcess(void);
void ParentProcess(void);

void main(void) {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        ChildProcess();
    } else {
        ParentProcess();
    }
}

void ChildProcess(void) {
    int  i;
    for (i = 1; i <= MAX_COUNT; i++) {
        printf("\tThis line is from child, value = %d\n", i);
    }
    printf("\t*** Child process is done ***\n");
}

void ParentProcess(void) {
    int  i;
    for (i = 1; i <= MAX_COUNT; i++) {
        printf("\tThis line is from parent, value = %d\n", i);
    }
    printf("\t*** Parent process is done ***\n");
}