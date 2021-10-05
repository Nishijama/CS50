// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
//Dictionary size
unsigned int wordCount = 0;
// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{

    //hash the word from the text
    unsigned int searchingHash = hash(word);
    //printf("%i, ", searchingHash);

    //create a traversal pointer
    node *querry;
    querry = table[searchingHash];

    if (querry == NULL)
    {
        return false;
    }

    while (querry != NULL)
    {
        //use case non-sensitive string comparison function

        if (strcasecmp(querry->word, word) == 0)
        {
            return true;
        }
        else
        {
            querry = querry->next;
        }

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int bucket;
    if (word[0] >= 97)
    {
        bucket = (int)word[0] - 97;
    }
    else
    {
        bucket = (int)word[0] - 65;
    }
    return bucket;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //
    // Allocate memory for a node, n

    // Open input file
    FILE *dict = fopen(dictionary, "r");

    if (!dict)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    // read a word at a time and create a new node for each word
    char newWord[LENGTH + 1];

    while (fscanf(dict, "%s", newWord) != EOF)
    {

        //allocate memory for a new node
        node *n;
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return 1;
        }

        //copy the word into the node
        strcpy(n->word, newWord);

        //set nodes next pointer to NULL
        n->next = NULL;

        //hash the word
        unsigned int location = hash(n->word);

        //insert the node to the correct bucket

        //if the bucket is empty, insert the node as the first element
        //node *head = table[location];
        if (table[location] == NULL)
        {
            table[location] = n;
            wordCount++;
        }
        else
        {
            n->next = table[location];
            table[location] = n;
            wordCount++;
        }

    }
    fclose(dict);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp, * cursor;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            tmp = table[i];
            cursor = table[i];
            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
        }
    }
    return true;
}
