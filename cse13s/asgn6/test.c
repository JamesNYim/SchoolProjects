#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "defines.h"
#include "code.h"
#include "io.h"
int main(void) {
    printf("---------------------------------------= Testing Nodes "
           "=----------------------------------------\n");
    Node *a = node_create('a', 10);
    Node *b = node_create('b', 4);
    Node *c = node_create('c', 6);
    Node *e = node_create('e', 9);
    Node *d = node_create('d', 14);
    ;
    //printing just nodes
    node_print(a);
    printf("\n");
    node_print(b);
    printf("\n");
    node_print(c);
    printf("\n");

    printf("---------------------------------------= Testing Queue "
           "=------------------------------------\n");
    //Queue Testing
    PriorityQueue *prioQueue = pq_create(4);

    //empty queue testing
    if (pq_empty(prioQueue)) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is filled\n");
    }

    //enqueue testing
    if (enqueue(prioQueue, a)) {
        printf("successfully queued\n");
    } else {
        printf("unsucessfully queues\n");
    }
    if (pq_empty(prioQueue)) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is filled\n");
    }

    enqueue(prioQueue, b);
    enqueue(prioQueue, c);
    enqueue(prioQueue, e);
    printf("printing queue\n");
    pq_print(prioQueue);

    if (pq_full(prioQueue)) {
        printf("Full\n");
    } else {
        printf("Empty?\n");
    }
    //node_delete(&a);
    //node_delete(&b);
    //node_delete(&c);
    //Testing dequeue
    if (dequeue(prioQueue, &d)) {
        printf("sucessfully dequeued\n");
    } else {
        printf("uncucessfully dequeued\n");
    }
    node_print(d);

    //Stack Testing
    Stack *stack = stack_create(10);

    //checking empty
    if (stack_full(stack)) {
        printf("Full\n");
    } else {
        printf("Empty?\n");
    }

    //checking stack size
    printf("stack size : %u\n", stack_size(stack));

    //pushing nodes
    if (stack_push(stack, a)) {
        printf("successfully pushed\n");
    } else {
        printf("unsucessfully pushed\n");
    }

    //checking empty after push
    if (stack_full(stack)) {
        printf("stack size : %u\n", stack_size(stack));
        printf("Full\n");
    } else {
        printf("stack size : %u\n", stack_size(stack));
        printf("Empty?\n");
    }
    stack_push(stack, b);
    stack_push(stack, c);

    //printing stack
    stack_print(stack);

    if (stack_pop(stack, &d)) {
        printf("successfully popped\n");
    } else {
        printf("unsucessfully popped\n");
    }
    node_print(d);
    node_delete(&a);
    node_delete(&b);
    node_delete(&c);
    node_delete(&d);
    node_delete(&e);
    stack_delete(&stack);
    pq_delete(&prioQueue);

    printf("---------------------------------------= Testing Code "
           "=------------------------------------\n");
    //Code testing
    Code code = code_init();
    printf("initial code size: %u\n", code_size(&code));

    //checking if code is emoty before setting bit
    if (code_empty(&code)) {
        printf("code size : %u\n", code_size(&code));
        printf("Empty\n");
    } else {
        printf("code size : %u\n", code_size(&code));
        printf("Full\n");
    }

    if (code_push_bit(&code, 1)) {
        printf("successfully pushed\n");
    } else {
        printf("unsucessfully pushed\n");
    }
    code_print(&code);

    printf("---------------------------------------= Testing IO "
           "=------------------------------------\n");
    //Testing IO
    uint8_t buffer[BLOCK];
    int infileFileNo = open("testFile", O_RDONLY);
    int bytesRead = read_bytes(infileFileNo, buffer, BLOCK);
    printf("bytesRead: %d\n", bytesRead);
    for (int i = 0; i < bytesRead; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}
