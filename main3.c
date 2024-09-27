#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child_process() {
    int num_iterations = random() % 30 + 1;  // Random number of iterations, max 30
    int i;
    for (i = 0; i < num_iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        int sleep_time = random() % 10 + 1;  // Sleep for a random time, max 10 sec
        sleep(sleep_time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }
    exit(0);  // Terminate child process
}

int main() {
    srandom(getpid());  // Seed random number generator with process id

    // Fork two child processes
    pid_t child1 = fork();
    if (child1 == 0) {
        // Inside first child process
        child_process();
    }

    pid_t child2 = fork();
    if (child2 == 0) {
        // Inside second child process
        child_process();
    }

    // Parent process waits for both children to complete
    int status;
    pid_t pid;
    int i;
    for (i = 0; i < 2; i++) {
        pid = wait(&status);
        printf("Child Pid: %d has completed\n", pid);
    }

    return 0;  // Parent process terminates
}
