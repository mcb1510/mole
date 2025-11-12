# CS 552 - Homework 4: Whack-a-Mole and Race Conditions

**Author:** Jim Buffenbarger, Miguel Carrasco Belmar 
**Date:** November 11, 2025  
**Course:** CS 552  
**Assignment:** HW4

## Overview
This project is an implementation of a simulation of the game Whack-a-Mole. This assignment's purpose is to learn
and practice single-process multi-thread (MT) programming, including the design and implementation
of MT-safe functions and data structures.
The simulation uses FLTK for graphical display.

## Files Included

- `deq.c` - Main implementation of the deque data structure from hw1
- `deq.h` - Header file with program interface hw1
- `error.h` - Error handling hw1
- `valgrind_results.txt` - File showing valgrind output
- `lawn.h` - Lawn interface
- `lawn.c` - Lawn  implementation
- `lawnimp.cc` - c++ implementation of FLTK graphics
- `lawnimp.h` - FLKT drawing functions interface
- `linkage.h` - C/C++ linkage helper
- `main.c` - Main file for the Whack-a-Mole simulation
- `mole.h` - Mole object and interface
- `mole.c` - Mole object implementation
- `mtq.h` - Multi-threaded queue wrapper interface
- `mtq.c` - Multi-threaded queue wrapper implementation
- `threads.h` - Thread management interface
- `threads.c` - Thread management implementation

## How to Run
make
./wam


## Resources
-Starter code provided by Professor Jim Buffenbarger.
-Operating Systems: Three Easy Pieces book
-GitHub Copilot
-Chat GPT5