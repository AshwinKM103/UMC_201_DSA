#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

trie_node *create_node() {
    trie_node *node = (trie_node *)malloc(sizeof(trie_node));
    if (node) {
        node->value = 0;
        node->is_end_of_word = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

Dict make_dict() {
    trie_dict *dict = (trie_dict *)malloc(sizeof(trie_dict));
    if (dict) {
        dict->root = create_node();
    }
    return (Dict)dict;
}

void free_trie(trie_node *node) {
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            free_trie(node->children[i]);
        }
        free(node);
    }
}

void free_dict(Dict dict_adt) {
    if (dict_adt) {
        trie_dict *dict = (trie_dict *)dict_adt;
        free_trie(dict->root);
        free(dict);
    }
}

int *get(Dict dict_adt, const char *key) {
    if (!dict_adt || !key) return NULL;
    trie_dict *dict = (trie_dict *)dict_adt;
    trie_node *node = dict->root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if (!node->children[index]) return NULL;
        node = node->children[index];
    }
    return node->is_end_of_word ? &(node->value) : NULL;
}

int set(Dict dict_adt, const char *key, int value) {
    if (!dict_adt || !key) return 0;
    trie_dict *dict = (trie_dict *)dict_adt;
    trie_node *node = dict->root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if (!node->children[index]) {
            node->children[index] = create_node();
            if (!node->children[index]) return 0;
        }
        node = node->children[index];
    }
    node->value = value;
    node->is_end_of_word = 1;
    return 1;
}

void print_trie(trie_node *node, char *prefix, int depth) {
    if (!node) return;
    if (node->is_end_of_word) {
        printf("%s: %d\n", prefix, node->value);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[depth] = 'a' + i;
            prefix[depth + 1] = '\0';
            print_trie(node->children[i], prefix, depth + 1);
        }
    }
}

void print_dict(Dict dict_adt) {
    if (!dict_adt) return;
    trie_dict *dict = (trie_dict *)dict_adt;
    char buffer[MAX_KEY_LENGTH + 1];
    print_trie(dict->root, buffer, 0);
}
