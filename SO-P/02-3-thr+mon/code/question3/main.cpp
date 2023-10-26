#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "process.h"

#define NUM_THREADS 2

static int count = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_even(void* arg) {
    printf("[thread_even] start\n");

    while (1) {
        pthread_mutex_lock(&mutex);

        while (count % NUM_THREADS != 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (count == 1) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        count--;
        printf("%d, PID = %d\n", count, getpid());

        pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);
    }

    printf("[thread_even] end\n");
    return NULL;
}

void* thread_odd(void* arg) {
    printf("[thread_odd] start\n");

    while (1) {
        pthread_mutex_lock(&mutex);

        while (count % NUM_THREADS != 1) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (count == 1) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        count--;
        printf("%d, PID = %d\n", count, getpid());

        pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);
    }

    printf("[thread_odd] end\n");
    return NULL;
}

int main(void) {
    int n;
    do {
        printf("Enter a value between 10 and 20: ");
        scanf("%d", &n);
    } while (n < 10 || n > 20);

    count = n;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t threads[NUM_THREADS];
    if (pthread_create(&threads[0], NULL, thread_even, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&threads[1], NULL, thread_odd, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(threads[0], NULL) != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(threads[1], NULL) != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    exit(EXIT_SUCCESS);
}