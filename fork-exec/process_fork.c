#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process ID: %d\n", getpid());
        printf("Child's parent process ID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent process ID: %d\n", getpid());
        printf("Parent's child process ID: %d\n", pid);
    }

    return 0;
}