// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int word_hashed = hash(word);
    node *node = table[word_hashed];

    while (node != NULL) //if there is a linked list, traverse
    {
        if (hash(word) == hash(node->word)) //strcmp(word, node->word) == 0
        {
            return true;
        }
        node = node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hash_number = 0;
    char c;
    int n;
    for (int i = 0; i < strlen(word); i++)
    {
        c = tolower(word[i]);
        // ASCII number and position of char used
        // to prevent identical hashes for names like Army and Mary
        if (c >= 97 && c <= 122)
        {
            n = c - 97 * (i + 1);
        }
        else if (c == 39)
        {
            n = round(39 / (i + 1));
        }
        hash_number += n;
    }
    return hash_number % N;
}

FILE *fptr;
char *dict;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    fptr = fopen(dictionary, "r");
    if (fptr == NULL)
    {
        printf("Could not open the dictionary.\n");
        return false;
    }
    dict = malloc(strlen(dictionary) + 1);
    strcpy(dict, dictionary);
    char word[LENGTH + 1];

    while (fscanf(fptr, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            printf("Ran out of memory");
            return false;
        }
        strcpy(newNode->word, word);
        int hashed_word = hash(newNode->word);

        newNode->next = table[hashed_word]; //next points to the current beginning
        table[hashed_word] = newNode; //the new node becomes the new beginning
    }
    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    FILE *cptr = fopen(dict, "r");
    if (cptr == NULL)
    {
        printf("Could not load the dictionary\n");
        return 0;
    }

    char c;
    int words = 0;

    while ((c = fgetc(cptr)) != EOF)
    {
        if (c == '\n' || c == ' ')
        {
            words++;
        }
    }
    fclose(cptr);
    free(dict);
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *Cnode = table[i];
        while (Cnode != NULL)
        {
            node *tmp = Cnode; //create temporary pointer to first node
            Cnode = tmp->next; //assign the node pointer to the next
            free(tmp); //free the tmp pointer
        }
        free(Cnode); //free the last node
    }
    return true;
}
