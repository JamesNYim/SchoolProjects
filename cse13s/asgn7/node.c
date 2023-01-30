#include "node.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *word) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n != NULL) {
        n->word = word;
        n->count = 1; //we set to 1 instead of 0 bc we now have 1 word when created
    }
    return n;
}

void node_delete(Node **n) {
    if (n) {
        *n = NULL;
        free(*n);
    }
}
void node_print(Node *n) {
    printf("[Count: %u Word: %s]\n", n->count, n->word);
}
