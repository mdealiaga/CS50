/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    return false;
    // TODO: implement a searching algorithm
   for (int i = 0; i<n; i++)
        {
            if (values[i] == value)
            {
            return true;
            }
           // if digit is right, stop, otherwise dont do anything, return false en of loop
        }
        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Implementing a selection sort algorithm
     for (int i = 0; i<n-1; i++)
     // runs through every number of array
        {
            int k = 0;
            //sets an integer to trigger while loop when it changes
            while (k == 0)
                {
                for (int o = i; o<n; o++)
                    {
                    if (values[o] < values[i])
                //searches whether a value is greater than values[i]. 
               
                        {
                        //Swaps the variables
                        int temp1 = values[i];
                        values[i] = values[o];
                        values[o] = temp1;
                        k = 1;
                        // changes k to = 1 to trigger exit of loop
                        }
                    }
                    k = 1;
                    //gets out of the while loop once everything is in order
                }
        }

        for (int i = 0; i<n; i++)
        //just for testing: prints the array to show what the swap did
          {
                printf("%i, ", values[i]);
          }
    return;
}
