/* 
 * File: mtq.c
 * Description: Implementation of multi-threaded queue.
 * Author(s): Miguel Carrasco Belmar
 * Date: 11/11/2025
 */

#include "mtq.h"
#include <stdlib.h>
#include "error.h"

// Multi-threaded queue structure
struct mtq {
    Deq deq;                  // unsafe queue
    pthread_mutex_t lock;     // one lock per queue
    pthread_cond_t not_full;  // signal for producers
    pthread_cond_t not_empty; // signal for consumers
    int capacity;             // maximum capacity of the queue
    int count;                // current number of items in the queue
};

// Create a new multi-threaded queue
Mtq mtq_new(int capacity) {
    // allocate the multi-threaded queue structure
    Mtq q = malloc(sizeof(*q));
    if (!q)
        ERROR("malloc() failed");

    q->deq = deq_new(); // create unsafe queue
    q->capacity = capacity; // set capacity
    q->count = 0; // initialize count

    // we initialize lock and condition variables
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);

    // we return the new multi-threaded queue
    return q;
}

// free the multi-threaded queue
void mtq_free(Mtq q) {
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->not_empty);
    deq_del(q->deq, 0);
    free(q);
}

// Put an item at the tail of the queue
void mtq_tail_put(Mtq q, void *item) {
    pthread_mutex_lock(&q->lock); // one thread at a time

    while (q->capacity > 0 && q->count >= q->capacity) {
        // wait until not full
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    deq_tail_put(q->deq, item); // put item at tail of unsafe queue
    q->count++; // increment count

    //signal waiting consumers, if any
    pthread_cond_signal(&q->not_empty);
    // unlock the mutex
    pthread_mutex_unlock(&q->lock);
}

// Get an item from the head of the queue
void *mtq_head_get(Mtq q) {
    pthread_mutex_lock(&q->lock); // one thread at a time

    // if the queue is empty, we wait 
    while (q->count == 0)
        pthread_cond_wait(&q->not_empty, &q->lock);
    
    // get item from head of unsafe queue
    void *item = deq_head_get(q->deq);
    q->count--; // decrement count

    // signal waiting producers, if any
    pthread_cond_signal(&q->not_full);

    // unlock the mutex
    pthread_mutex_unlock(&q->lock);
    return item;
}