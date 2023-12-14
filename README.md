## libh
*Another* C collection library.

### API
Add library files directly into project or compile using `makefile` into `.a` library object.

Import into project by:
```C
#include "libh.h"
```

#### Stack
A bounded stack. (TODO: Make this arena allocated)
```C
stack   stack_init();
int     stack_empty(stack *stack);
int     stack_full(stack *stack);
int     stack_pop(stack *stack);
int     stack_peek(stack *stack);
int     stack_push(stack *stack, uint16_t value);
```

#### Arena
A heap-allocated memory-arena for efficient dynamic datastructure allocation.
```C
arena arena_init(ptrdiff_t cap);
void *arena_alloc(arena *a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count);
```

Usage:
```C
arena a = arena_init(1 << 16);
map *root = arena_new(&a, map, 1);
```

#### Hashtable
An open-addressed hashtable that uses double-hashing.
```C
struct hashtable hashtable_init();
char *hashtable_get(struct hashtable *t, char *key);
char *hashtable_intern(struct hashtable *t, char *key);
char *hashtable_unintern(struct hashtable *t, char *key);
static uint64_t hashtable_idx_lookup(uint64_t h, int exp, uint32_t i);
```
#### Hashmap
An arena-backed hashmap.
```C
struct map {
    map *child[4];
    str     key;
    char *value;
};
char **hashmap_upsert(map **m, str key, arena *perm);
```

Usage:
```C
arena a = arena_init(1 << 16);
map *root = arena_new(&a, map, 1);
str key = {"test", 4};
char **value = hashmap_upsert(&root, key, &a);
```

#### Priority Queue
A bounded max-priority queue.
```C
priority_q pq_init();
int pq_full(priority_q *pq);
int pq_empty(priority_q *pq);
int pq_add(priority_q *pq, uint32_t value);
int pq_pop(priority_q *pq, uint32_t *value);
int pq_peek(priority_q *pq, uint32_t *value);
```
