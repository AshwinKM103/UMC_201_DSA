#ifndef DICT_H
#define DICT_H

#include "dict_adt.h"

#define ALPHABET_SIZE 26

typedef struct trie_node {
    int value;
    struct trie_node *children[ALPHABET_SIZE];
    int is_end_of_word;
} trie_node;

typedef struct trie_dict {
    trie_node *root;
} trie_dict;

#endif
