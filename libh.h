#include <stdint.h>



/* -------------------------- STACK ----------------------------- */
#define LIBH_STACK_EXP 15

typedef struct {
    uint16_t data[1 << LIBH_STACK_EXP];
    int top;
} Stack;

Stack   stack_init();
int     stack_empty(Stack *stack);
int     stack_full(Stack *stack);
int     stack_pop(Stack *stack);
int     stack_peek(Stack *stack);
int     stack_push(Stack *stack, uint16_t value);


/* ------------------------ HASHTABLE --------------------------- */
#define LIBH_HASHTABLE_EXP 15
#define LIBH_HASHTABLE_INIT { {0}, 0 }

struct hashtable {
    char *ht[1 << LIBH_HASHTABLE_EXP];
    uint32_t len;
};

uint64_t hash_fnv(char *s, uint32_t len); // FNV-1a hashing algorithm
struct hashtable hash_table_init();
char *hash_intern(struct hashtable *t, char *key);
char *hash_unintern(struct hashtable *t, char *key);
uint64_t hash_idx_lookup(uint64_t h, int exp, uint32_t i);
