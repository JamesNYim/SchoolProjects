#include "code.h"
#include "defines.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
Code code_init(void) {
    Code c;
    c.top = 0;
    return c;
}
uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    return c->top == 0;
}

bool code_full(Code *c) {
    return c->top == MAX_CODE_SIZE;
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i > ALPHABET / 8 || i == 0) {
        return false;
    }
    c->bits[i / 8] |= (1 << (i % 8)); //set bit to 1
    return true;
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i > ALPHABET / 8 || i == 0) {
        return false;
    }
    c->bits[i / 8] &= ~(1 << (i % 8)); //set bit to 0
    return true;
}
bool code_get_bit(Code *c, uint32_t i) {
    if (c->bits[i / 8] << (i % 8) == 1) {
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    c->bits[c->top] = bit;
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    *bit = c->bits[c->top];
    c->top -= 1;
    return true;
}
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("index: %u, bit: %u\n", i, c->bits[i]);
    }
}
