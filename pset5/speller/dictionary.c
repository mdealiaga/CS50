/**
 * Implements a dictionary's functionality.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "dictionary.h"

//DEFINE HASHTABLE SIZE - 
//TODO: CHANGE TO FUNCTION OF SIZE

#define HASHTABLE_SIZE 500
    
int word_count = 0;
bool loaded = true;

//DEFINE NODE STRUCT
    typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }
    node;

///DEFINE FUNCTIONS


    //Hash function - https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
    int hash_it(char* needs_hashing)
    {
        unsigned int hash = 0;
        for (int i=0, n=strlen(needs_hashing); i<n; i++)
            hash = (hash << 2) ^ needs_hashing[i];
        return hash % HASHTABLE_SIZE;
    } 
    
///INITIALISE ARRAY FOR HASH TABLE
    node *hashtable[HASHTABLE_SIZE];
    


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

//Store word copy
int len = strlen(word);
char word_copy[len + 1];

for (int i = 0; i < len; i++)
{
    word_copy[i] = tolower(word[i]);
}
  
word_copy[len] = '\0';
  
  
//Calculate hashtable
int n = hash_it(word_copy);
    
//Traverse Linked list
node *cursor = hashtable[n];

while (cursor != NULL)
{
    // check if word is in dict
    if (strcmp(cursor->word, word_copy) == 0)
    {
        return true; 
    }
    else
    {
    cursor = cursor->next;
    }
}
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    
    //OPEN DICTIONARY
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open.\n");
        unload();
        return 1;
    }
    
    
    
    node *new_node = malloc(sizeof(node)); 
    //SCAN DICT WORD BY WORD
    while (fscanf(fp, "%s", new_node->word) != EOF)
    {
    //MALLOC NODE FOR EACH NEW WORD
    node *new_node = malloc(sizeof(node));
    new_node->next = NULL;
            
            
            //intert into hashtable
            int n = hash_it(new_node->word);
            node* head = hashtable[n];
            if (head == NULL)
                {
                    hashtable[n] = new_node;
                    //creates notes if hash bucket is empty
                }
            else
                {
                    new_node->next = hashtable[n];
                    hashtable[n] = new_node;
                    //else adds to the chain
                }
            word_count += 1;

        
    }
    
    // close text
    fclose(fp);
    loaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if (loaded == 1)
    {
        return word_count;
    }
    else
    {
    return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    loaded = false;
    return true;
}
