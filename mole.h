/* 
 * File: mole.h
 * Description: Header file for mole interface.
 * Author(s): Jim Buffenbarger
 * Date: 11/11/2025
 */

#ifndef MOLE_H
#define MOLE_H

#include "lawn.h"

// type definition for Mole
typedef void *Mole;
// Create a new mole associated with the given lawn
extern Mole mole_new(Lawn l, int vimlo, int vimhi);
// Whack the given mole and free its resources
extern void mole_whack(Mole m);

#endif
