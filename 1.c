#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int pid = fork();
    if (pid < 0)
    {
        printf("Child not created\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child is created PID: %d\n", getpid());
    }
    else
    {
        sleep(1);
        printf("Parent created PID: %d\n", getpid());
    }
    return 0;
}
