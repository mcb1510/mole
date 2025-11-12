/* 
 * File: main.c
 * Description: Main file for producer-consumer mole whacking simulation.
 * Author(s): Jim Buffenbarger - Miguel Carrasco Belmar
 * Date: 11/11/2025
 */

 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "deq.h"
#include "lawn.h"
#include "mole.h"
#include "threads.h"
#include "mtq.h"
 
// Producer thread function
static void *produce(void *a) {
  // extract arguments
  void **arg = a;
  
  //Get the queue and lawn from arguments
  Mtq mtq = (Mtq)arg[0];
  Lawn l = (Lawn)arg[1];
  //Create a new mole and put it in the queue
  mtq_tail_put(mtq, mole_new(l,0,0));
  // free argument memory
  free(arg);
  return 0;
}

// Consumer thread function
static void *consume(void *a) {
  // extract arguments
  void **arg = a;
  Mtq mtq = (Mtq)arg[0]; //Get the queue from arguments
  Mole m = mtq_head_get(mtq); //Get a mole from the queue
  mole_whack(m); //Whack the mole
  // free argument memory
  free(arg);
  return 0;
}

// Main function
int main() {
  srandom(time(0));
  const int n=10; //number of producer and consumer threads
  Lawn lawn=lawn_new(0,0); //Create a new lawn
  Mtq mtq = mtq_new(4); //Create a multi-threaded queue with capacity 4

  // Create producer threads
  void *producer_args[]= {mtq, lawn};
  pthread_t *producers = create_thread(n, produce, producer_args);
  
  // Create consume threads
  void *consume_args[]= {mtq, lawn};
  pthread_t *consumers = create_thread(n, consume, consume_args);
  // Wait for all threads to finish
  join_thread(n, producers);
  join_thread(n, consumers);

  // Clean up resources
  mtq_free(mtq);
  lawn_free(lawn);
}
