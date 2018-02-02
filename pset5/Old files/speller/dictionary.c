/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>


/**
 * Returns true if word is in dictionary else false.
 */
 
     //create struct
       typedef struct node
    {
        bool is_word;
        struct node *children[27];
    }
    node;
    
    node *root;
    


//open file
FILE *ptr = fopen(dictionary, "r");
if (file == NULL)
{
    printf("Could not open\n");
    return false;
}


 node* root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }







bool check(const char *word)
{
    // TODO
    return false;
}












/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    /*
    Every node contains an array of node pointers
        one for every letter in the alphabet + '\'''
        each element in the array points to another node
            if that node is NULL, then that letter isn't the next letter in any word in that sequence
    every node indicates whether it's the last character of a word
    
    
    for every dictionary word, iterate through the trie
    each element in children corresponds to a different letter
    check the value at children[i]
        if NULL, malloc a new node, have children[i] point to it
        if not NULL. move to new node and continue
    if at end of word, set is_word to true
    
    
    */
    
    

    
    
    //open dictionary
//    
    
    //set up trie
    
   
    
//traversal pointer
//bool find(node* root);

    
    
    /*
     root = calloc(1, sizeof(node));
    if (root == NULL)
        return false;
    */
    
/*
  char c;
    
    while ((c = fgetc(ptr)) != EOF)
    {
        insertnode(ptr, c, root);
    }
    
    if ((c = fgetc(ptr)) == EOF)
    {
        return true;
    }
    
    */
    
    return false;

}








/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
