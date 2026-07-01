// Write a program called launcher.c that:

// Prints the parent's PID.
// Calls fork().
// In the child:
// Prints its PID and PPID.
// Executes the date command using execl().
// In the parent:
// Prints "Waiting for child...".
// Sleeps for 10 seconds.
// Prints "Parent exiting".

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
        printf("Child's PPID: %d\n", getppid());

        execl("/bin/date", "date", NULL);
        perror("execl failed");
    } else {
        // Parent process
        printf("Waiting for child...\n");
        sleep(10);
        printf("Parent exiting\n");
    }

    return 0;
}