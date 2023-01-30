#include "pq.h"
#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct PriorityQueue {
    uint32_t tail;
    uint32_t head;
    uint32_t capacity;
    Node **nodes;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq != NULL) {
        pq->capacity = capacity;
        pq->tail = 0;
        pq->head = 0;
        pq->nodes = (Node **) calloc(capacity, sizeof(Node *));
        if (pq->nodes) {
            return pq;
        }
        free(pq);
    }
    return NULL;
}

void pq_delete(PriorityQueue **q) {
    if (q) {
        free((*q)->nodes);
        free(*q);
    }
}

bool pq_empty(PriorityQueue *q) {
    return q->head == q->tail;
}

bool pq_full(PriorityQueue *q) {
    if (q) {
        return (q->head == q->capacity);
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->head;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (q) {
        if (pq_full(q)) {
            return false;
        }

        q->nodes[q->head] = n;
        //Sorting the Queue
        uint32_t queueSize = pq_size(q);
        if (queueSize == 0) {
            q->head = (q->head + 1);
            return true;
        }

        for (uint32_t i = pq_size(q); i > 0; i--) {
            Node previousNode = *q->nodes[i - 1];
            Node currentNode = *q->nodes[i];
            if (currentNode.frequency < previousNode.frequency) {
                Node tempNode = *q->nodes[i - 1];
                q->nodes[i - 1] = q->nodes[i];
                q->nodes[i] = &tempNode;
            }
        }
        q->head = (q->head + 1);
        return true;
    } else {
        return false;
    }
}
bool dequeue(PriorityQueue *q, Node **n) {
    if (q) {
        if (pq_empty(q)) {
            return false;
        }
        **n = *q->nodes[q->tail];

        uint32_t queueSize = pq_size(q);
        for (uint32_t i = 1; i < queueSize; i++) {
            q->nodes[i - 1] = q->nodes[i];
        }

        q->head = q->head - 1;
        return true;
    } else {
        return false;
    }
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < pq_size(q); i++) {
        Node *n = q->nodes[i];
        node_print(n);
    }
}
