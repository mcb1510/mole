#include "threads.h"
#include <stdlib.h>
#include <pthread.h>
#include "error.h"

pthread_t * create_thread(int n, ThreadFunc func, void **arg) {
    pthread_t *t_ids = malloc(n * sizeof(pthread_t));
    if (!t_ids)
        ERROR("malloc() failed for thread IDs");
    for (int i = 0; i < n; i++) {
        void **args = malloc( 2 * sizeof(void *));
        if (!args)
            ERROR("malloc() failed for thread arguments");
        args[0] = arg[0]; //queue
        args[1] = arg[1]; //lawn (or null for consumer)
        pthread_create(&t_ids[i], NULL, func, args);
    }
    return t_ids;
}

void join_thread(int n, pthread_t *threads) {
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
}