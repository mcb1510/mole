#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "deq.h"
#include "lawn.h"
#include "mole.h"
#include "threads.h"
 
static void *produce(void *a) {
  void **arg = a;
  Deq q = (Deq)arg[0];
  Lawn l = (Lawn)arg[1];
  deq_tail_put(q, mole_new(l,0,0));
  free(arg);
  return 0;
}

static void *consume(void *a) {
  void **arg = a;
  Deq q = (Deq)arg[0];
  Mole m = deq_head_get(q);
  mole_whack(m);
  free(arg);
  return 0;
}


int main() {
  srandom(time(0));
  const int n=10;
  Lawn lawn=lawn_new(0,0);
  Deq q = deq_new(); //creates dequeu

  // Create producer threads
  void *producer_args[]= {q, lawn};
  pthread_t *producers = create_thread(n, produce, producer_args);
  // Create consume threads
  void *consume_args[]= {q, lawn};
  pthread_t *consumers = create_thread(n, consume, consume_args);
  // Wait for all threads to finish
  join_thread(n, producers);
  join_thread(n, consumers);

  // // Creates moles and adds them to the deque
  // for (int i=1; i<=n; i++)
  // {
  //   Mole m = produce(lawn);
  //   deq_tail_put(q, m); // we put the mole at the tail of the deque
  // }
  //  // gets moles from the deque and whacks them
  // for (int i=1; i<=n; i++)
  // { 
  //   Mole m = deq_head_get(q); // we get the mole from the head of the deque
  //   consume(m);
  // }

  // We clean up
  deq_del(q, NULL);
  lawn_free(lawn);
}
