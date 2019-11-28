/*
 * myshell - My tine shell program for tsh assignment
 *
 * <Hyeonseo Jo 2018009143>
 */

#include <stdio.h>
#include <stdlib.h>     /* exit() */
#include <unistd.h>
#include <string.h>     /* strcpy, strlen, strchr */
#include <sys/types.h>  
#include <sys/wait.h>   /* waitpid() */ 
#include <errno.h>

/* Misc manifest constants */
#define MAXLINE     1024    /* max line size */
#define MAXARGS      128    /* max args on a command line */


/* Global variables */
extern char** environ;      /* defined in libc */
char prompt[] ="bsh> ";     /* command line prompt */
/* End global variables */


/* Function prototypes */
void eval(char* cmdline);
int builtin_cmd(char **argv);

int parseline(const char* cmdline, char** argv);

void unix_error(char* msg);
void app_error(char* msg);

/*
 * main - The shell's main routine
 */
int main(int argc, char** argv) {
    
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */


    /* Execute the shell's read/eval loop */
    while (1) {
        
    /* Read command line */
    if (emit_prompt) {
        printf("%s", prompt);
    }
    if (fgets(cmdline, MAXLINE, stdin) == NULL) {
        app_error("fgets error");
    }
    if (feof(stdin)) { /* End of file (ctrl-d) */
        exit(0);
    }

    /* Evaluate the command line */
    eval(cmdline);
    }

    printf("It reaches to never reaches!\n");
    exit(0); /* control never reaches here */
}

/*
 * eval -
 *
 * 
 */
void eval(char* cmdline) {
    
    char* argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if (argv[0] == NULL) {
        return; /* Ignore empty lines */
    }
    if (!builtin_cmd(argv)) {
        //printf("not a builtin_cmd, so fork/exec!\n");
        if ((pid = fork()) == 0) { /* Child runs user job */
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* Parent waits for foreground job to terminate */
        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                unix_error("waitfg: waitpid error");
            }
        } else {
            printf("%d %s", pid, cmdline);
        }
    }
    return;
}

/* 
 * parseline - Parse the command line and build argv array.
 *
 * Characters enclosed in single quotes are treated as a single
 * argument. Return true if the user has requested a BG job, false
 * the user has requested a FG job.
 */
int parseline(const char* cmdline, char** argv) {

    static char array[MAXLINE];
    char* buf = array;
    char* delim;
    int argc;   /* number of args */
    int bg;     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf) - 1] = ' '; /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) { /* ignore leading spaces */
        buf++;
    }

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'') {
        buf++;
        delim = strchr(buf, '\'');
    }
    else {
        delim = strchr(buf, ' ');
    }

    while (delim) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) {
            buf++;
        }
        if (*buf == '\'') {
            buf++;
            delim = strchr(buf, '\'');
        }
        else {
            delim = strchr(buf, ' ');
        }
    }
    argv[argc] = NULL;

    if (argc == 0) { /* ignore black line */
        return 1;
    }

    /* should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0) {
        argv[--argc] = NULL;
    }
    return bg;
}

/*
 * builtin_cmd - If the user has typed a built-in command then execute
 * it immediately.
 */
int builtin_cmd(char **argv) {
    
    int argc = 0;
    char* args = argv[argc];

    if (!strcmp(args, "jobs")) {
        printf("(builtin_cmd: jobs)\n");
        return 1;
    }
    else if (!strcmp(args, "quit")) {
        exit(0);
    }
    else if (!strcmp(args, "bg") && argv[++argc] != NULL) {
        printf("(builtin_cmd: bg <jid>: %d)\n", atoi(argv[argc]));
        return 1;
    }
    else if (!strcmp(args, "fg") && argv[++argc] != NULL) {
        printf("(builtin_cmd: fg <jid>: %d)\n", atoi(argv[argc]));
        return 1;
    }
    return 0;   /* not a builtin command */
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char* msg) {
    fprintf(stdout, "%s\n", msg);
    exit(1);
}