#include <stdio.h>

#include "libh.h"


stack stack_init() {
    stack s;
    s.top = -1;
    return s;
}

int stack_empty(stack *stack) {
    return stack->top == -1;
}

int stack_full(stack *stack) {
    return stack->top == (1 << LIBH_STACK_EXP) - 1;
}

int stack_pop(stack *stack) {
    if (stack_empty(stack)) {
        return -1;
    };
    return stack->data[stack->top--];
}

int stack_peek(stack *stack) {
    if (stack_empty(stack)) {
        return -1;
    };
    return stack->data[stack->top];
}

int stack_push(stack *stack, uint16_t value) {
    if (stack_full(stack)) {
        return -1;
    }
    return stack->data[++stack->top] = value;
}
