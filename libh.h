#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>


/* -------------------------- STACK ----------------------------- */
#define LIBH_STACK_EXP 15

typedef struct {
    uint16_t data[1 << LIBH_STACK_EXP];
    int top;
} stack;

stack   stack_init();
int     stack_empty(stack *stack);
int     stack_full(stack *stack);
int     stack_pop(stack *stack);
int     stack_peek(stack *stack);
int     stack_push(stack *stack, uint16_t value);


/* -------------------------- ARENA ----------------------------- */
#define arena_new(a, t, n)  (t *)arena_alloc(a, sizeof(t), _Alignof(t), n)

typedef struct {
    char *beg;
    char *end;
} arena;

arena arena_init(ptrdiff_t cap);
void *arena_alloc(arena *a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count);


/* ------------------------ HASHTABLE --------------------------- */
#define LIBH_HASHTABLE_EXP 15
#define LIBH_HASHTABLE_INIT { {0}, 0 }

struct hashtable {
    char *ht[1 << LIBH_HASHTABLE_EXP];
    uint32_t len;
};

uint64_t hash_fnv(char *s, uint32_t len); // FNV-1a hashing algorithm
struct hashtable hashtable_init();
char *hashtable_get(struct hashtable *t, char *key);
char *hashtable_intern(struct hashtable *t, char *key);
char *hashtable_unintern(struct hashtable *t, char *key);
static uint64_t hashtable_idx_lookup(uint64_t h, int exp, uint32_t i);


/* ------------------------- HASHMAP ---------------------------- */
typedef struct {
    char *data;
    ptrdiff_t len;
} str;

typedef struct map map;
struct map {
    map *child[4];
    str     key;
    char *value;
};

char **hashmap_upsert(map **m, str key, arena *perm);
