#include "node.h"
#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **nodes;
};

Stack *stack_create(uint32_t capacity) {

    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->nodes = (Node **) calloc(capacity, sizeof(Node *));
        if (s->nodes == NULL) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (s) {
        free((*s)->nodes);
        free(*s);
    }
}

bool stack_empty(Stack *s) {
    return s->top <= 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        s->capacity *= 2;
        s->nodes = (Node **) realloc(s->nodes, s->capacity * sizeof(Node *));
    }
    s->nodes[s->top] = n;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    **n = *s->nodes[s->top];
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < stack_size(s); i++) {
        Node *n = s->nodes[i];
        node_print(n);
    }
}
