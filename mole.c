/* 
 * File: mole.c
 * Description: Implementation of mole interface.
 * Author(s): Jim Buffenbarger
 * Date: 11/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mole.h"
#define LAWNIMP
#include "lawnimp.h"
#undef LAWNIMP
#include "error.h"

// Generate a random integer between lo and hi
static int rdm(int lo, int hi) {
  return random()%(hi-lo+1)+lo;
}

// Create a new mole associated with the given lawn and vim range
extern Mole mole_new(Lawn l, int vimlo, int vimhi) {
  if (!vimlo) vimlo=1;
  if (!vimhi) vimhi=5;

  LawnRep lawn=(LawnRep)l;
  MoleRep mole=(MoleRep)malloc(sizeof(*mole));
  if (!mole) ERROR("malloc() failed");
  mole->size=lawn->molesize;
  // Initialize the mole's position and vim values
  int max=lawn->lawnsize*lawn->molesize;
  mole->x=rdm(0,max-1);
  mole->y=rdm(0,max-1);
  mole->vim0=rdm(vimlo,vimhi);
  mole->vim1=rdm(vimlo,vimhi);
  mole->vim2=rdm(vimlo,vimhi);
  mole->lawn=lawn;
  mole->box=lawnimp_mole(mole);
  return mole;
}

// Whack the mole and free its resources
extern void mole_whack(Mole m) {
  lawnimp_whack(m);
  free(m);
}

