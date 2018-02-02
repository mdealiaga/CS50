#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string();
//checks that name has an input
    if (name != NULL)
    {
        int x = 1;
//prints the first digit (because of the way code works, need to print this first)
        if (isupper(name[0]))
        {
            printf("%c", name[0]);
        }
        else
        {
            printf("%c", toupper(name[0]));
        }
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            if (name[i] == ' ')
                {
                x += 1;
//adds a value to x every time a new word is made
                }
            if (x%2 == 0)
//if x is even, print the word and add 1 to x - so just print first of each word
                {
             x += 1;
                if (isupper(name[i+1]))
                    {
                printf("%c", name[i+1]);
                    }
                else
                    {  
                 printf("%c", toupper(name[i+1]));
//makes the printed letter uppercase if it isn't already
                    }
                 }
        }
        printf("\n");
    }
}