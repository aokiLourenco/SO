#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main (void)
{
    int counter = 1;

    pid_t ret = pfork();
    
    if (ret == 0)
    {
        for (int i = 1; i<=10; i++)
        {
            printf("%d, PID = %d, PPID = %d\n", counter, getpid(), getppid());
            counter++;
        }
    } else { // counter from 10 to 20
        for (int i = 1; i<=10; i++)
        {
            usleep(200000);
            printf("%d, PID = %d, PPID = %d\n", counter+10, getpid(), getppid());
            counter++;
        }
    }

    return EXIT_SUCCESS;
}