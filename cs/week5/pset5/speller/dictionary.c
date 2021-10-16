// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;
int dict_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashV = hash(word);

    node *n = table[hashV];

    while(n != NULL){
        if(strcasecmp(word, n->word) == 0){
            return true;
        }
        n=n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long total = 0;

    for (int i = 0; i< strlen(word); i++){
        //printf("%i\n",tolower(word[i]));
        total += tolower(word[i]);
    }

    //printf("%s",)
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *ptr = fopen(dictionary, "r");

    if(ptr == NULL){
        printf("Error during the openning of %s", dictionary);
        return false;
    }

    char next[LENGTH+1];

    while(fscanf(ptr, "%s", next)!=EOF){
        node *n = malloc(sizeof(node));
        if(n==NULL){
            return false;
        }

        strcpy((*n).word, next);
        int hashV = hash(next);

        n->next = table[hashV];
        table[hashV] = n;
        dict_size++;

    }

    fclose(ptr);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i<N; i++){
        node *n = table[i];

        while(n!=NULL){
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        if(n==NULL && i == N-1){
            return true;
        }
    }

    return false;
}
