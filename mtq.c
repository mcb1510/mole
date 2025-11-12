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

// Get the current length of the queue
int mtq_len(Mtq q) {
    pthread_mutex_lock(&q->lock); // one thread at a time
    int len = q->count; // get current count
    pthread_mutex_unlock(&q->lock); // unlock the mutex
    return len;
}

// HEAD OPERATIONS//

// Put an item at the head of the queue
void mtq_head_put(Mtq q, void *item) {
    pthread_mutex_lock(&q->lock); // one thread at a time

    while (q->capacity > 0 && q->count >= q->capacity) {
        // wait until not full
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    deq_head_put(q->deq, item); // put item at head of unsafe queue
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

// Get the ith item from the head of the queue
Data mtq_head_ith(Mtq q, int i) {
    pthread_mutex_lock(&q->lock); // one thread at a time
    Data item = deq_head_ith(q->deq, i); // get ith item from head of unsafe queue
    pthread_mutex_unlock(&q->lock); // unlock the mutex
    return item;
}


// Remove a specific item from the head of the queue
Data mtq_head_rem(Mtq q, Data d) {
    pthread_mutex_lock(&q->lock); // one thread at a time

    Data item = deq_head_rem(q->deq, d); // remove specific item from head of unsafe queue
    q->count--; // decrement count
    // signal waiting producers, if any
    pthread_cond_signal(&q->not_full);
    // unlock the mutex
    pthread_mutex_unlock(&q->lock);
    return item;
}

// TAIL OPERATIONS//

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

// Get an item from the tail of the queue
void *mtq_tail_get(Mtq q) {
    pthread_mutex_lock(&q->lock); // one thread at a time
    // if the queue is empty, we wait 
    while (q->count == 0)
        pthread_cond_wait(&q->not_empty, &q->lock);

    // get item from tail of unsafe queue
    void *item = deq_tail_get(q->deq);
    q->count--; // decrement count

    // signal waiting producers, if any
    pthread_cond_signal(&q->not_full);

    // unlock the mutex
    pthread_mutex_unlock(&q->lock);
    return item;
}
// Get the ith item from the tail of the queue
Data mtq_tail_ith(Mtq q, int i) {
    pthread_mutex_lock(&q->lock); // one thread at a time
    Data item = deq_tail_ith(q->deq, i); // get ith item from tail of unsafe queue
    pthread_mutex_unlock(&q->lock); // unlock the mutex
    return item;
}

// Remove a specific item from the tail of the queue
Data mtq_tail_rem(Mtq q, Data d) {
    pthread_mutex_lock(&q->lock); // one thread at a time

    Data item = deq_tail_rem(q->deq, d); // remove specific item from tail of unsafe queue
    q->count--; // decrement count
    // signal waiting producers, if any
    pthread_cond_signal(&q->not_full);
    // unlock the mutex
    pthread_mutex_unlock(&q->lock);
    return item;
}

//helper functions
void mtq_map(Mtq q, DeqMapF f) {
    pthread_mutex_lock(&q->lock); // one thread at a time
    deq_map(q->deq, f); // apply function to each item in unsafe
    pthread_mutex_unlock(&q->lock); // unlock the mutex
}

// convert the queue to a string
Str mtq_str(Mtq q, DeqStrF f) {
    pthread_mutex_lock(&q->lock); // one thread at a time
    Str s = deq_str(q->deq, f); // convert unsafe queue to string
    pthread_mutex_unlock(&q->lock); // unlock the mutex
    return s;   
}