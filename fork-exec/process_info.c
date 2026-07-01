#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("Current process ID: %d\n", pid);

    pid_t ppid = getppid();
    printf("Parent process ID: %d\n", ppid);
    return 0;
}