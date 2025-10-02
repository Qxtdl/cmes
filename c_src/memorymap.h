#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include "globals.h"

// Note that the post interface is just a indicator to the user,
// you can decide how to encode the fail cause.
#define POST_SUCCESS 2
#define POST_FAILURE 1
#define POST_RESULT     ((volatile bool *)0xFFF8) // Power-On Self Test Result (0 = pass, 1 = fail)
#define POST_FAIL_CAUSE ((volatile u8   *)0xFFF7) // Power-On Self Test Fail Cause

#endif // MEMORYMAP_H