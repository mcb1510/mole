#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

typedef void *(*ThreadFunc)(void *);

pthread_t * create_thread(int n, ThreadFunc func, void **arg);
void join_thread(int n, pthread_t *threads);

#endif // THREADS_H