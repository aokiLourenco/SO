#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "process.h"

#define SHM_NAME "/counter_shm"

typedef struct {
    int pcounter;
} shdata;

int main (void)
{

    int shmid;

    size_t size = sizeof(shdata);

    shmid = pshmget(IPC_PRIVATE, size, 0600 | IPC_CREAT | IPC_EXCL);

    void* p = pshmat(shmid, NULL, 0);

    shdata* data = (shdata*) p;
    
    data -> pcounter = 1;

    pid_t ret = pfork();
    
    if (ret == -1) {
        perror("pfork");
        exit(EXIT_FAILURE);
    }else if (ret == 0) {

        int input;
        do {
            printf("Value [10, 20]: ");
            scanf("%d", &input);
        } while (input < 10 || input > 20);
        

        for (int i = 1; i<=input; i++)
        {
            printf("%d, (%d)", data->pcounter, getpid());
            data->pcounter++;
        }
    } else { // counter from 10 to 20
        usleep(200000);

        while (data -> pcounter < 10) {
            printf("%d, (%d)", data->pcounter, getpid());
            data->pcounter--;
        }

        pshmdt(p);
        pshmctl(shmid, IPC_RMID, NULL);

        exit(EXIT_SUCCESS);
    }
}