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
    char **authors;
    double *distances;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    //checking if queue container was allocated
    if (pq != NULL) {
        pq->capacity = capacity;
        pq->tail = 0;
        pq->head = 0;
        pq->authors = (char **) calloc(capacity, sizeof(char *));
        pq->distances = (double *) calloc(capacity, sizeof(double));

        //checking if arrays successfully allocated
        if (pq->authors && pq->distances) {
            return pq;
        }
        free(pq);
    }
    return NULL;
}

void pq_delete(PriorityQueue **q) {
    if (q) {
        free((*q)->authors);
        free((*q)->distances);
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

bool enqueue(PriorityQueue *q, char *author, double distance) {
    if (q) {
        if (pq_full(q)) {
            return false;
        }

        q->authors[q->head] = author;
        q->distances[q->head] = distance;
        //Sorting the Queue
        uint32_t queueSize = pq_size(q);
        if (queueSize == 0) {
            q->head = (q->head + 1);
            return true;
        }

        for (uint32_t i = pq_size(q); i > 0; i--) {
            if (q->distances[i] < q->distances[i - 1]) {
                //swapping locations
                double tempDist = q->distances[i];
                q->distances[i] = q->distances[i - 1];
                q->distances[i - 1] = tempDist;

                char *tempString = q->authors[i];
                q->authors[i] = q->authors[i - 1];
                q->authors[i - 1] = tempString;
            }
        }
        q->head = (q->head + 1);
        return true;
    } else {
        return false;
    }
}
bool dequeue(PriorityQueue *q, char **author, double *distance) {
    if (q) {
        if (pq_empty(q)) {
            return false;
        }
        *author = q->authors[q->tail];
        *distance = q->distances[q->tail];
        uint32_t queueSize = pq_size(q);
        for (uint32_t i = 1; i < queueSize; i++) {
            q->distances[i - 1] = q->distances[i];
            q->authors[i - 1] = q->authors[i];
        }
        q->head = q->head - 1;

        return true;
    } else {
        return false;
    }
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < pq_size(q); i++) {
        printf("Author: %s, Distance: %lf\n", q->authors[i], q->distances[i]);
    }
}
