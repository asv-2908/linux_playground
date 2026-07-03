#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Parent PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
        sleep(3);
        int *p = NULL;
        *p = 42; // This will cause a segmentation fault
    } else {
        // Parent process
        printf("Waiting for child...\n");
        int status;
        pid_t pid2 = waitpid(pid, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status))
        {
            printf("Child %d exited normally\n", pid2);
            printf("Exit status = %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child %d terminated by signal %d\n", pid2, WTERMSIG(status));
        }
        else
        {
            printf("Child did not exit normally\n");
        }
        printf("Parent exiting\n");
    }

    return 0;
}