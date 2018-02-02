#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int PHeight;
    do
    {
    //prompts user for pyramid height
    printf("How tall do you want the pyramids to be? (Max is 23)\n");
    PHeight = get_int();
    }
    //sets max height to 23 and min to 0
    while (PHeight > 23 || PHeight < 0);

//prints the pyramid
 for (int o = 0; o < PHeight; o++)
    {
    for (int i = o+1; i < PHeight; i++)
    {
    //prints the spaces before the pyramid to give it it's shape
    //essentially starts with height-1 spaces and counts down
        printf(" ");
    }
    for (int i = -1; i < o; i++)
    {
    //prints the first pyramid hashes for each row
    printf("#");
    }
    //prints the two spaces in each row
    printf("  ");
    for (int i = -1; i < o; i++)
    {
    //prints the second row of hashes
    printf("#");
    }
    //breaks each line
    printf("\n");
    }
}