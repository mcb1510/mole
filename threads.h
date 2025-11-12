/* 
 * File: threads.h
 * Description: Header file for thread management.
 * Author(s): Miguel Carrasco Belmar
 * Date: 11/11/2025
 */

#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

// Thread function type
typedef void *(*ThreadFunc)(void *);

// Create n threads executing the given function with the provided arguments
pthread_t * create_thread(int n, ThreadFunc func, void **arg);
// Join n threads and free their resources
void join_thread(int n, pthread_t *threads);

#endif // THREADS_H