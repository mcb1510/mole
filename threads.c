/* 
 * File: threads.c
 * Description: Implementation of thread management.
 * Author(s): Miguel Carrasco Belmar
 * Date: 11/11/2025
 */

#include "threads.h"
#include <stdlib.h>
#include <pthread.h>
#include "error.h"

// Create n threads executing the given function with the provided arguments
pthread_t * create_thread(int n, ThreadFunc func, void **arg) {
    // allocate array for thread IDs
    pthread_t *t_ids = malloc(n * sizeof(pthread_t));
    if (!t_ids)
        ERROR("malloc() failed for thread IDs");
    // create n threads
    for (int i = 0; i < n; i++) {
        void **args = malloc( 2 * sizeof(void *));
        if (!args)
            ERROR("malloc() failed for thread arguments");
        // set up arguments for the thread function
        args[0] = arg[0]; //queue
        args[1] = arg[1]; //lawn 
        // create the thread
        pthread_create(&t_ids[i], NULL, func, args);
    }
    // return the array of thread IDs
    return t_ids;
}

// Join n threads and free their resources
void join_thread(int n, pthread_t *threads) {
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
}