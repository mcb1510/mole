/* 
 * File: lawn.c
 * Description: Implementation of lawn data structure
 *              and associated functions.
 * 
 * Author(s): Jim Buffenbarger
 * Date: 11/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <X11/Xlib.h>   

#include "lawn.h"
#define LAWNIMP
#include "lawnimp.h"
#undef LAWNIMP
#include "error.h"

// This function serves as the pthread entry point.
static void *run(void *l) {
  LawnRep r=(LawnRep)l;
  return lawnimp_run(r);
}

// Create a new lawn with specified lawn size and mole size.
extern Lawn lawn_new(int lawnsize, int molesize) {
  if (!lawnsize) lawnsize=40;
  if (!molesize) molesize=15;

  XInitThreads(); // initialize X11 for multi-threading
  // We allocate and initialize the lawn representation
  LawnRep lawn=(LawnRep)malloc(sizeof(*lawn));
  if (!lawn) ERROR("malloc() failed");
  lawn->lawnsize=lawnsize;
  lawn->molesize=molesize;
  // Initialize the lawn window using the implementation function
  lawn->window=lawnimp_new(lawnsize,molesize);
  // Start the lawn simulation thread
  if (pthread_create(&lawn->thread,0,run,lawn))
    ERROR("pthread_create() failed: %s",strerror(errno));
  return lawn;
}

// Free the lawn and associated resources.
extern void lawn_free(Lawn l) {
  LawnRep r=(LawnRep)l;
  lawnimp_free(r->window);
  if (pthread_join(r->thread,0))
      ERROR("pthread_join() failed: %s",strerror(errno));
  free(r);
}
