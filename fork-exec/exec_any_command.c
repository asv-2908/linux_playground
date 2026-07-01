#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s command\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) // Child process
    {
        execlp(argv[1], argv[1], NULL);

        perror("exec");
    }

    sleep(1);

    printf("Parent done\n");

    return 0;
}