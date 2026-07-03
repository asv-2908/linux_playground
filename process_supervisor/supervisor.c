#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_WORKERS 3

pid_t workers[NUM_WORKERS];

pid_t launch_worker(int id)
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        char worker_id[10];
        sprintf(worker_id, "%d", id);

        execl("./worker", "./worker", worker_id, NULL);
        perror("execl");

        exit(EXIT_FAILURE);
    }

    printf("Worker %d started with pid %d\n", id, pid);
    return pid;
}

int main()
{
    printf("=================================\n");
    printf(" Mini Process Supervisor\n");
    printf(" Supervisor PID = %d\n", getpid());
    printf("=================================\n\n");

    for(int i = 0; i < NUM_WORKERS; i++)
    {
        workers[i] = launch_worker(i+1);
    }

    while(1)
    {
        int status;

        pid_t dead_pid = waitpid(-1, &status, 0);

        if (dead_pid < 0)
        {
            perror("waitpid");
            break;
        }

        int worker_index = -1;

        for(int i = 0; i < NUM_WORKERS; i++)
        {
            if (dead_pid == workers[i])
            {
                worker_index = i;
                break;
            }
        }

        if (worker_index == -1)
        {
            printf("Unknown child exited\n");
            break;
        }

        printf("\n---------------------------------\n");
        printf("Worker %d (PID=%d) terminated\n", worker_index + 1, dead_pid);

        if (WIFEXITED(status))
        {
            printf("Reason: Normal Exit\n");
            printf("Exit Code = %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Reason: Crashed\n");
            printf("Signal = %d\n", WTERMSIG(status));
        }

        printf ("Restarting Worker %d\n", worker_index + 1);
        workers[worker_index] = launch_worker(worker_index + 1);

        printf("---------------------------------\n\n");
    }

    return 0;
}