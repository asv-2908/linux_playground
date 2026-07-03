#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Worker %s started with PID: %d\n", argv[1], getpid());
    int id = atoi(argv[1]);

    sleep(rand() % 10 + 3);

    if (id == 2)
    {
        int *p = NULL;
        *p = 100;
    }

    printf("Worker %s exiting\n", argv[1]);

    return id;
}