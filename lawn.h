/* 
 * File: lawn.h
 * Description: Header file for Lawn data structure and associated functions.
 * 
 * Author(s): Jim Buffenbarger
 * Date: 11/11/2025
 */

#ifndef LAWN_H
#define LAWN_H

// type definition for Lawn
typedef void *Lawn;

// Create a new lawn with specified lawn size and mole size.
extern Lawn lawn_new(int lawnsize, int molesize);
// Free the lawn and associated resources.
extern void lawn_free(Lawn l);

#endif
