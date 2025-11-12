/* 
 * File: lawnimp.h
 * Description: Header file for lawn implementation functions.
 * Author(s): Jim Buffenbarger
 * Date: 11/11/2025
 */

 #ifndef LAWNIMP_H
#define LAWNIMP_H

#ifndef LAWNIMP
#error Do not #include this file, directly.
#endif

#include <pthread.h>

#include "linkage.h"

// Lawn representation structure
typedef struct {
  int lawnsize;
  int molesize;
  void *window;
  pthread_t thread;
} *LawnRep;

// Mole representation structure
typedef struct {
  int size;
  int x,y;
  int vim0,vim1,vim2;
  void *lawn;
  void *box;
} *MoleRep;

// Create a new lawn window
extern LINKAGE void* lawnimp_new(int lawnsize, int molesize);
// Run the lawn event loop
extern LINKAGE void* lawnimp_run(LawnRep l);
// Create a new mole in the lawn
extern LINKAGE void* lawnimp_mole(MoleRep m);
// Whack a mole in the lawn
extern LINKAGE void  lawnimp_whack(MoleRep m);
// Free the lawn window
extern LINKAGE void  lawnimp_free(void* w);

#endif
