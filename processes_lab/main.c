#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>     // write, getpid

#define MAX_COUNT 200
#define BUF_SIZE  100

int main(void) {
    pid_t pid;
    int i;
    char buf[BUF_SIZE];

    fork();                    // duplicate process
    pid = getpid();            // each gets its own pid

    for (i = 1; i <= MAX_COUNT; i++) {
        int n = snprintf(buf, sizeof(buf),
                         "This line is from pid %d, value = %d\n", (int)pid, i);
        write(1, buf, (size_t)n);  // unbuffered -> avoids printf interleaving weirdness
    }
    return 0;
}