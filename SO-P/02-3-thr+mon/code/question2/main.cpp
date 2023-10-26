#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"

static int count;

void* thread_main(void* arg)
{
    printf("\n[thread_main] start\n");
    usleep(50000);
    int N2;
    
    printf("Value[10;20]: ");
    scanf("%d", &N2);

    if (N2 < 10 || N2 > 20) {
        printf("Error: input out of range [10, 20]\n");
        exit(EXIT_FAILURE);
    }

    while(count != N2) {
        printf("%d\n", count);
        count++;
        usleep(50000);
    }

    printf("[thread_main] end\n");
    return NULL;
}

int main(int agrc, char* argv[])
{
    printf("[main] start\n");

    int N1;

    pthread_t thread;
    
    printf("Value[1;9]: ");
    scanf("%d", &N1);

    if (N1 < 0 || N1 > 9) {
        printf("Error: input out of range [1, 9]");
        exit(EXIT_FAILURE);
    }

    thread_create(&thread, NULL, thread_main, NULL);
    thread_join(thread, NULL);

    while (count > 0) {
        printf("%d\n", count);
        count--;
        usleep(50000);
    }

    printf("[main] end\n");
    
    return 0;
}
