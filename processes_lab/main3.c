#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>   // wait, macros
#include <unistd.h>     // fork, getpid, getppid, sleep
#include <time.h>       // time for better seeding

static void child_process(void);

int main(void) {
    pid_t kids[2];

    // create 2 children
    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            child_process();          // never returns
        } else if (pid > 0) {
            kids[i] = pid;            // track PIDs (optional)
        } else {
            perror("fork");
            // if fork fails for one child, still wait for any that succeeded
        }
    }

    // parent waits for both children
    for (int i = 0; i < 2; i++) {
        int status = 0;
        pid_t done = wait(&status);
        if (done == -1) {
            perror("wait");
            break;
        }
        if (WIFEXITED(status)) {
            printf("Child Pid: %d has completed with exit status: %d\n",
                   (int)done, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child Pid: %d terminated by signal: %d\n",
                   (int)done, WTERMSIG(status));
        } else {
            printf("Child Pid: %d finished (non-normal)\n", (int)done);
        }
    }
    return 0;
}

static void child_process(void) {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    // good seed: unique per child & different runs
    srandom((unsigned)(time(NULL) ^ pid));

    // random loop count: 1..30
    int loops = (int)(random() % 30) + 1;

    for (int i = 0; i < loops; i++) {
        int snooze = (int)(random() % 10) + 1;   // 1..10 seconds
        printf("Child Pid: %d is going to sleep for %d seconds!\n", (int)pid, snooze);
        sleep((unsigned)snooze);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", (int)pid, (int)ppid);
    }
    exit(0);
}