/* hello_signal.c */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int ready = 0;

void handler(int sig) {
    (void)sig; // avoid unused warning
    printf("Hello World!\n");
    ready = 1;
}

int main(void) {
    signal(SIGALRM, handler);  // register handler
    alarm(5);                  // trigger after 5 seconds

    while (!ready) {
        pause();               // wait until signal arrives
    }

    printf("Turing was right!\n");
    return 0;
}