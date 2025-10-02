/* hello_signal.c */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>     // for alarm() and pause()

// A flag that both main and the handler can see
volatile int ready = 0;

// The signal handler — runs automatically every 5s
void handler(int sig) {
    (void)sig;               // unused parameter
    printf("Hello World!\n");
    ready = 1;               // tell main() to print its line
    alarm(5);                // schedule another signal 5s later
}

int main(void) {
    signal(SIGALRM, handler);  // register handler for SIGALRM
    alarm(5);                  // send first signal after 5s

    while (1) {
        pause();               // wait for a signal
        if (ready) {
            printf("Turing was right!\n");
            ready = 0;         // reset flag
        }
    }

    return 0;
}