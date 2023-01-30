#include "node.h"
#include "code.h"
#include "defines.h"
#include "pq.h"
#include <stdint.h>
#include "io.h"
#include "stack.h"
#include <stdlib.h>
Node *build_tree(uint64_t hist[static ALPHABET]) {
    //Getting the amount of symbols in the histogram
    uint32_t amount_of_symbols = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            amount_of_symbols++;
        }
    }
    PriorityQueue *pq = pq_create(amount_of_symbols);

    //Making a node and queuing it
    for (int symbol = 0; symbol < ALPHABET; symbol++) {
        if (hist[symbol] > 0) {
            Node *n = node_create(symbol, hist[symbol]);
            enqueue(pq, n);
            //do I node_delete here?
        }
    }

    //making parent node
    while (1 < pq_size(pq)) {
        Node *left;
        Node *right;
        dequeue(pq, &left);
        dequeue(pq, &right);
        Node *parent_node = node_join(left, right);
        enqueue(pq, parent_node);
    }

    //returning root
    Node *root;
    dequeue(pq, &root);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    uint8_t *popped_bit = 0;
    //Checking if Node is a leaf
    if (root) {
        if (!root->left && !root->right) {
            table[root->symbol] = c;
        } else {
            //left bit
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, popped_bit);

            //right bit
            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, popped_bit);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    if (root) {
        uint8_t L = 'L';
        uint8_t I = 'I';
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!root->left && !root->right) {
            write_bytes(outfile, &L, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            write_bytes(outfile, &I, 1);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(nbytes);
    uint16_t i = 0;
    while (i <= nbytes) {
        if (tree[i] == 'L') {
            i++;
            Node *n = node_create(tree[i], 0);
            stack_push(s, n);
            i++;
            break;
        } else if (tree[i] == 'I') {
            i++;
            Node *left_child = node_create(tree[i], 0);
            i++;
            Node *right_child = node_create(tree[i], 0);
            Node *parent = node_join(left_child, right_child);
            stack_push(s, parent);
            i++;
            break;
        }
    }
    Node *root;
    stack_pop(s, &root);
    return root;
}

void delete_tree(Node **root) {
    if (*root) {
        if (&((*root)->left)) {
            delete_tree((&((*root)->left)));
        }
        if (&((*root)->right)) {
            delete_tree((&(*root)->right));
        }
    } else {
        root = NULL;
        node_delete(root);
    }
}
