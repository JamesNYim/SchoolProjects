#include "node.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n != NULL) {
        n->right = NULL;
        n->left = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

void node_delete(Node **n) {
    n = NULL;
    free(n);
}

Node *node_join(Node *left, Node *right) {
    uint64_t combined_frequency = left->frequency + right->frequency;
    Node *parent_node = node_create('$', combined_frequency);
    parent_node->left = left;
    parent_node->right = right;
    return parent_node;
}

void node_print(Node *n) {
    printf("[frequency: %lu, symbol: %u]\n", n->frequency, n->symbol);
}
