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
#define MAXJOBS      16   /* max jobs at any point in time */

#define VERSION      0.1    /* version of the bsh */

/* Job states */

#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

/* 
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

// TODO: verbose input
/* Global variables */
extern char** environ;      /* defined in libc */
char prompt[] ="bsh> ";     /* command line prompt */
int verbose = 0;            /* if true, print additional output */

struct job_t {              /* The job struct */
    pid_t pid;              /* job PID */
    int jid;                /* job ID [1, 2, ...] */
    int state;              /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE];  /* command line */
};
struct job_t jobs[MAXJOBS];
/* End global variables */


/* Function prototypes */
void eval(char* cmdline);
int builtin_cmd(char **argv);

void waitfg(pid_t pid);

int parseline(const char* cmdline, char** argv);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);

void usage(void);
void unix_error(char* msg);
void app_error(char* msg);

/*
 * main - The shell's main routine
 */
int main(int argc, char** argv) {
    
    char c;
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */

    while ((c = getopt(argc, argv, "hvp")) != EOF) {
        switch (c) {
        case 'h':
            usage();
            break;
        case 'v':
            verbose = 1;
            break;
        case 'p':
            emit_prompt = 0;
            break;
    default:
            usage();
        }
    }

    /* Install the signal handlers */

    

    /* Initialize the job list */
    initjobs(jobs);

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

    exit(0); /* control never reaches here */
}

/*
 * eval - Evaluate the command line that the user has just typed in
 *
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job in running in
 * the foreground, wait for it to terminate and then return. Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.
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
            waitfg(pid);
        } else {
            printf("(%d) %s", pid, cmdline);
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
        printf("(builtin_cmd: bg <job>: %d)\n", atoi(argv[argc]));
        return 1;
    }
    else if (!strcmp(args, "fg") && argv[++argc] != NULL) {
        printf("(builtin_cmd: fg <job>: %d)\n", atoi(argv[argc]));
        return 1;
    }
    return 0;   /* not a builtin command */
}

void waitfg(pid_t pid) {
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        unix_error("waitfg: waitpid error");
    }
}

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

void clearjob(struct job_t *job) {
    job->pid = 0;
    job->jid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs) {
    int i;
    for (i = 0; i < MAXJOBS; i++)
	clearjob(&jobs[i]);
}


/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void) {

    printf("Welcome to the B Shell.\n");
    printf("version: %2.1f\n\n", VERSION);

    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -b   print infomation about b-shell\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n\n");

    printf("List of all built-in command that my B Shell supports.\n\n");

    printf("jobs\tjobs     -- lists all background jobs.\n");
    printf("quit\tquit     -- terminates the shell\n");
    printf("bg\tbg <job> -- sending <job> a SIGCONT sinal, runs it in the background.\n");
    printf("fg\tfg <job> -- sending <job> a SIGCONT sinal, runs it in the foreround.\n\n");
    exit(1);
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