#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 < 0)
    {
        printf("Child not created\n");
        return 1;
    }
    else if (pid1 == 0)
    {
        printf("Child Process 1 (PID: %d): Listing files\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Parent Process (PID: %d): First child completed\n", getpid());
        pid2 = fork();
        if (pid2 < 0)
        {
            printf("Child not created\n");
            return 1;
        }
        else if (pid2 == 0)
        {
            printf("Child Process 2 (PID: %d): Second child\n", getpid());
            sleep(5);
            printf("Child Process 2 (PID: %d): Work done\n", getpid());
            exit(0);
        }
        else
        {
            printf("Parent Process (PID: %d): Exiting \n", getpid());
            exit(0);
        }
    }
}
