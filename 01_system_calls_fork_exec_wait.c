/* 1. Linux System Calls: fork(), exec() and wait() */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Child process is running.\n");
        execlp("ls", "ls", NULL);
        perror("exec failed");
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("Parent: Child process completed.\n");
    }
    else
        perror("fork failed");

    return 0;
}
