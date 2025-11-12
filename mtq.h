/* 
 * File: mtq.h
 * Description: Header file for multi-threaded queue.
 * Author(s): Miguel Carrasco Belmar
 * Date: 11/11/2025
 */

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
// Get the current length of the queue
int mtq_len(Mtq q);

// Get an item from the head of the queue
// if the queue is empty, we wait until an item is available
void *mtq_head_get(Mtq q);
// Put an item at the head of the queue
void mtq_head_put(Mtq q, void *item);
// Get the ith item from the head of the queue
Data mtq_head_ith(Mtq q, int i);
// Remove a specific item from the head of the queue
Data mtq_head_rem(Mtq q, Data d);

// Put an item at the tail of the queue
// if the queue is full, we wait until space is available
void mtq_tail_put(Mtq q, void *item);
// Get an item from the tail of the queue
// if the queue is empty, we wait until an item is available
void *mtq_tail_get(Mtq q);
// Get the ith item from the tail of the queue
Data mtq_tail_ith(Mtq q, int i);
// Remove a specific item from the tail of the queue
Data mtq_tail_rem(Mtq q, Data d);

//helper functions
void mtq_map(Mtq q, DeqMapF f); // foreach
Str  mtq_str(Mtq q, DeqStrF f); // toString

#endif // MTQ_H