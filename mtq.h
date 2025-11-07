#ifndef MTQ_H
#define MTQ_H

#include <pthread.h>
#include "deq.h"

// Multi-threaded queue structure
typedef struct mtq *Mtq;

// Create a new multi-threaded queue
// capacity: maximum number of items in the queue
// capacity of 0 means unbounded
Mtq mtq_new(int capacity);

// Free the multi-threaded queue
void mtq_free(Mtq q);

// Put an item at the tail of the queue
// if the queue is full, we wait until space is available
void mtq_tail_put(Mtq q, void *item);

// Get an item from the head of the queue
// if the queue is empty, we wait until an item is available
void *mtq_head_get(Mtq q);

#endif // MTQ_H