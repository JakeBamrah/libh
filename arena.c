#include <string.h>
#include <stdlib.h>

#include "libh.h"


arena arena_init(ptrdiff_t capacity) {
    arena a = {0};
    a.beg = malloc(capacity);
    a.end = a.beg ? a.beg + capacity : 0;
    return a;
}

void *arena_alloc(arena *a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count) {
    // compute paddding of object (until alignment evenly divides address)
    ptrdiff_t avail = a->end - a->beg;
    ptrdiff_t padding = -(uintptr_t)a->beg & (align - 1);
    if (count > (avail - padding) / size) { // check if memory available
        abort();
    }

    ptrdiff_t total = size * count;
    char *p = a->beg + padding;
    a->beg += padding + total;
    return memset(p, 0, total);
}
