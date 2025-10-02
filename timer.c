#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

// global counter for number of alarms (seconds)
int seconds = 0;

// handler for SIGALRM (triggered every second)
void handle_alarm(int sig) {
    seconds++;
    printf("Tick %d seconds passed...\n", seconds);
    alarm(1); // schedule the next alarm after 1 second
}

// handler for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("\nProgram ran for %d seconds. Exiting now.\n", seconds);
    exit(0);
}

int main() {
    // register handlers
    signal(SIGALRM, handle_alarm);
    signal(SIGINT, handle_sigint);

    // start first alarm
    alarm(1);

    // busy wait forever
    while (1) {
        pause(); // wait for a signal to arrive
    }

    return 0;
}