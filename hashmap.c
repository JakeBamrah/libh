#include <string.h>
#include <stdbool.h>

#include "libh.h"


static bool equals(str a, str b)
{
    return a.len == b.len && !memcmp(a.data, b.data, a.len);
}

char **hashmap_upsert(map **m, str key, arena *perm) {
    for (uint64_t h = hash_fnv(key.data, key.len); *m; h <<= 2) {
        if (equals(key, (*m)->key)) {
            return &(*m)->value;
        }
        m = &(*m)->child[h>>62];
    }
    if (!perm) {
        return 0;
    }

    *m = arena_new(perm, map, 1);
    (*m)->key = key;
    return &(*m)->value;
}
