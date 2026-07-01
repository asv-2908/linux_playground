#include <stdio.h>
#include <unistd.h>

// This program demonstrates the use of fork and exec to create a child process that executes the "ls" command.
// This is how usually works in Unix-like operating systems. The parent process will continue running while the 
// child process executes the "ls" command.

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Child launching ls\n");

        execl("/bin/ls", "ls", "-l", NULL);

        perror("exec failed");
    }
    else
    {
        printf("Parent continues running\n");

        sleep(5);

        printf("Parent exiting\n");
    }

    return 0;
}