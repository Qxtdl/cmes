#include <stddef.h>

#include "globals.h"
#include "stdio.h"

extern char _heap_start[];
extern char _heap_end[];

static char *heap_ptr = NULL;

void heap_init(void) {
    heap_ptr = _heap_start;
}

void *malloc(u32 size) {
    if (!heap_ptr) heap_init();

    size = (size + 3) & ~3;

    char *alloc = heap_ptr;

    if (heap_ptr + size > _heap_end) {
        return NULL;
    }

    printf("malloc %x : %x", size, heap_ptr);
    heap_ptr += size;
    return (void *)alloc;
}

void free_all(void) {
    heap_ptr = _heap_start;
}
