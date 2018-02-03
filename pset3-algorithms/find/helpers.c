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
// Uses a binary search algorithm
    if (n < 0)
    {
    return false;
    }

    int endpoint = n;
    int startpoint = 0;
    while (startpoint<=endpoint)
    // exits the loop if q becomes less than 0 (so number isn't there)
        {
            int midpoint = (startpoint+endpoint)/2;
            if (value == values[midpoint])
            {
            return true;
            // returns true if value is exactly midpoint
            }
            else if (value < values[midpoint])
            {
                endpoint = midpoint-1;
                // halves midpoint if value is less than midpoint
            }
            else
            {
                startpoint = midpoint+1;
                // goes to middle of midpoint and end if value is more than midpoint
            }
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


