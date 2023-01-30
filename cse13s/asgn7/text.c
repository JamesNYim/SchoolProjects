#include "metric.h"
#include "parser.h"
#include "bf.h"
#include "ht.h"
#include "text.h"
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define WORD "[a-zA-Z]+"
uint32_t noiselimit; // Number of noise words to filter out.

struct Text {
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count;
};

Text *text_create(FILE *infile, Text *noise) {

    //Allocating the Text
    Text *t = (Text *) malloc(sizeof(Text));
    t->word_count = 0;
    //Checking if text was successfully allocated
    if (t == NULL) {
        return NULL;
    } else {
        //Allocating hash table and checking if successful
        t->ht = ht_create(1 << 19);
        if (t->ht == NULL) {
            free(t);
            t = NULL;
            return NULL;
        }

        //Allocating bloom filter and checking if successful
        t->bf = bf_create(1 << 21);
        if (t->bf == NULL) {
            ht_delete(&t->ht);
            t->ht = NULL;
            free(t);
            t = NULL;
            return NULL;
        }

        //Initializing regex and checking if successful
        regex_t re;
        if (regcomp(&re, WORD, REG_EXTENDED)) {
            ht_delete(&t->ht);
            t->ht = NULL;
            bf_delete(&t->bf);
            t->bf = NULL;
            free(t);
            t = NULL;
            return NULL;
        }

        char *word = "";
        while ((word = next_word(infile, &re)) != NULL) {
            //Making all lowercase
            for (uint32_t i = 0; i < strlen(word); i++) {
                word[i] = tolower(word[i]);
            }

            if (noise == NULL) {
                ht_insert(t->ht, word);
                bf_insert(t->bf, word);
                t->word_count += 1;
            } else {
                if (text_contains(noise, word) == false) {
                    ht_insert(t->ht, word);
                    bf_insert(t->bf, word);
                    t->word_count += 1;
                }
            }
        }
        regfree(&re);
    }
    return t;
}

void text_delete(Text **text) {
    if (text) {
        ht_delete(&(*text)->ht);
        bf_delete(&(*text)->bf);
        free(*text);
    }
}

double text_dist(Text *text1, Text *text2, Metric metric) {
    //Variables
    double distance_between = 0;
    double text1_word = 0;
    double text2_word = 0;
    HashTableIterator *hti_1 = hti_create(text1->ht);
    HashTableIterator *hti_2 = hti_create(text2->ht);

    //looping through the hash tables
    Node *text1_node = ht_iter(hti_1);
    Node *text2_node = ht_iter(hti_2);
    while (text1_node != NULL && text2_node != NULL) {
        //Checking if word exists
        if (ht_lookup(text1->ht, text1_node->word) != NULL
            && ht_lookup(text2->ht, text2_node->word)) {
            //Getting vector pairs
            text1_word = text_frequency(text1, text1_node->word);
            text2_word = text_frequency(text2, text2_node->word);
            printf("word1: %f, word2: %f\n", text1_word, text2_word);
            //Choosing which metric and computing
            //Manhattan
            if (metric == MANHATTAN) {
                distance_between += fabs(text1_word - text2_word);
            }

            //Euclidean
            else if (metric == EUCLIDEAN) {
                distance_between += (text1_word - text2_word);
                distance_between += distance_between * distance_between;
            }

            //Cosine
            else if (metric == COSINE) {
                distance_between += (text1_word - text2_word);
            }
        }
        text1_node = ht_iter(hti_1);
        text2_node = ht_iter(hti_2);
    }
    //if cosine we sub 1
    if (metric == COSINE) {
        distance_between += 1 - distance_between;
    }

    return distance_between;
}

double text_frequency(Text *text, char *word) {
    Node *current_node = ht_lookup(text->ht, word);
    if (current_node) {
        printf("current_node->count: %u | text->word_count: %u\n", current_node->count,
            text->word_count);
        return (double) current_node->count / text->word_count;
    }
    return 0;
}

bool text_contains(Text *text, char *word) {
    if (bf_probe(text->bf, word)) {
        if (ht_lookup(text->ht, word) != NULL) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void text_print(Text *text) {
    printf("----Text----\n");
    printf("\n");
    printf("-=HT=-\n");
    ht_print(text->ht);
    //	printf("\n");
    //	printf("-=BF=-\n");
    //	bf_print(text->bf);
    printf("\n");
    printf("Word Count: %u\n", text->word_count);
}
