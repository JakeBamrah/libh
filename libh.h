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
