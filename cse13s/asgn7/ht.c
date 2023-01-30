#include "ht.h"
#include "node.h"
#include "salts.h"
#include "speck.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Definition for HashTable
struct HashTable {
    uint64_t salt[2]; //the salt to use for hash function
    uint32_t size; //the number of slots in the hash table
    Node **slots; //array of hash table items
};

//Definition for HashTable Iterator
struct HashTableIterator {
    HashTable *table; //hash table to iterate over
    uint32_t slot; //the current slot the iterator is on
};
//Creating the hash table
HashTable *ht_create(uint32_t size) {
    HashTable *h = (HashTable *) calloc(1, sizeof(HashTable));
    if (h) {
        h->size = size;
        h->salt[0] = SALT_HASHTABLE_LO;
        h->salt[1] = SALT_HASHTABLE_HI;
        h->slots = (Node **) calloc(size, sizeof(Node *));
        if (h->slots) {
            return h;
        }
        free(h);
    }
    return NULL;
}

//Deleting a hash table
void ht_delete(HashTable **ht) {
    if (ht) {
        HashTableIterator *hti = hti_create(*ht);
        for (Node *current_node = ht_iter(hti); current_node != NULL; current_node = ht_iter(hti)) {
            node_delete(&current_node);
        }
        hti_delete(&hti);
        free((*ht)->slots);
        free(*ht);
    }
}

//Getting the size of hash table
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

//Searching for a word in the hash table
Node *ht_lookup(HashTable *ht, char *word) {
    HashTableIterator *hti = hti_create(ht);
    for (Node *current_node = ht_iter(hti); current_node != NULL; current_node = ht_iter(hti)) {
        if (strcmp(current_node->word, word) == 0) {
            return current_node;
        }
    }
    hti_delete(&hti);

    //if the word is not found
    return NULL;
}

Node *ht_insert(HashTable *ht, char *word) {
    Node *current_node = ht_lookup(ht, word);
    uint32_t hash_index = hash(ht->salt, word) % ht_size(ht);

    //If the word already is in the hash table
    if (current_node != NULL) {
        ht->slots[hash_index] = current_node;
        ht->slots[hash_index]->count += 1;
        return ht->slots[hash_index];
    }

    //If the word DNE in the hash table
    else if (current_node == NULL /*and the table isnt full */) {

        current_node = node_create(word);
        ht->slots[hash_index] = current_node;
        return ht->slots[hash_index];
    }
    //returning null if unsucessful
    return NULL;
}

void ht_print(HashTable *ht) {
    HashTableIterator *hti = hti_create(ht);
    for (Node *currentNode = ht_iter(hti); currentNode != NULL; currentNode = ht_iter(hti)) {
        if (currentNode != NULL) {
            node_print(currentNode);
        }
    }
    hti_delete(&hti);
}

HashTableIterator *hti_create(HashTable *ht) {
    HashTableIterator *hti = (HashTableIterator *) malloc(sizeof(HashTableIterator));
    if (hti) {
        hti->table = ht;
        hti->slot = 0;
    }
    return hti;
}

void hti_delete(HashTableIterator **hti) {

    free(*hti);
}

Node *ht_iter(HashTableIterator *hti) {
    uint32_t table_size = ht_size(hti->table);

    //looping through the table
    while (hti->slot < table_size) {

        //checking if the current slot is filled
        if (hti->table->slots[hti->slot]) {
            hti->slot = hti->slot + 1;
            return hti->table->slots[hti->slot - 1];
        }
        hti->slot = (hti->slot + 1);
    }
    //if iterated throughout the entire hash table w/out finding an entry
    return NULL;
}
