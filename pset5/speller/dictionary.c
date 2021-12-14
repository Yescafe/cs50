// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 80000;

// Hash table
node *table[N];

// size of dictionary
unsigned int zise = 0u;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int idx = hash(word);
    node *itr = table[idx];
    while (itr != NULL) {
        const char *c1 = word, *c2 = itr->word;
        while (*c1 != '\0' && *c2 != '\0') {
            if (tolower(*c1++) != tolower(*c2++)) break;
        }
        if (*c1 == '\0' && *c2 == '\0')
            return true;
        itr = itr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // polynomial rolling hash
    const char *c = word;
    unsigned p = 31;
    long long power_of_p = 1;
    long long hash_val = 0;
    while (*c != '\0') {
        hash_val = (hash_val + (tolower(*c++) - 'a' + 1) * power_of_p) % N;
        power_of_p = (power_of_p * p) % N;
    }
    return (hash_val % N + N) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; ++i) {
        table[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if (!file) {
        fprintf(stderr, "Dictionary open failed.\n");
        return false;
    }

    char word[LENGTH + 1];
    while (~fscanf(file, "%s", word)) {
        size_t len = strlen(word);
        while (word[len - 1] == '\n')
            word[len-- - 1] = '\0';

        if (check(word)) continue;

        int idx = hash(word);
        node* next = table[idx];
        table[idx] = (node *) malloc(sizeof(node));
        strcpy(table[idx]->word, word);
        table[idx]->next = next;
        ++zise;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return zise;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; ++i) {
        while (table[i] != NULL) {
            node *next = table[i]->next;
            free(table[i]);
            table[i] = next;
        }
        table[i] = NULL;
    }
    zise = 0;
    return true;
}
