#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include "globals.h" // See for "bool" definition

// Note that the post interface is just a indicator to the user,
// you can decide how to encode the fail cause.
#define POST_SUCCESS 2
#define POST_FAILURE 1
#define POST_RESULT     ((volatile bool *)0xFFF8) // Power-On Self Test Result (0 = pass, 1 = fail)
#define POST_FAIL_CAUSE ((volatile u8   *)0xFFF7) // Power-On Self Test Fail Cause

// TTY Console
#define TTY_LOC     ((volatile char *)0xFFF6) // TTY Console Location
#define TTY_CHAR    ((volatile char *)0xFFF5) // TTY Console Location
#define TTY_WRITE   ((volatile bool *)0xFFF4) // Write to TTY Console
#define TTY_CLEAR   ((volatile bool *)0xFFF3) // Clear TTY Console

// User Input
#define USER_READY  ((volatile bool *)0xFFF2) // User Input Ready Flag !!! READING RESETS THIS TO 0 IF IT'S 1 !!!
#define USER_ASCII  ((volatile char *)0xFFF1) // User Input ASCII Character

#endif // MEMORYMAP_H