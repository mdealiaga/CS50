#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    if (argc == 2)
    //ensures only one argument is entered after command name
    {
    int k = atoi(argv[1]);
    //converts command into an integer
    printf("plaintext:");
       string plaintext = get_string();
       //asks user for a plaintext input
       printf("ciphertext:");
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            if isalpha(plaintext[i])
            //checks if alphabetic character
                {
                    if isupper(plaintext[i])
                    {
                        printf("%c", ((plaintext[i]-65+k)%26)+65);
                        // converts text into code using equation
                    }
                    if islower(plaintext[i])
                    {
                        printf("%c", ((plaintext[i]-97+k)%26)+97);
                        // converts text into code using equation
                    }
                }
            else
                {
                printf("%c", plaintext[i]);
                //outputs text if it's not an alphabetic character
                }
    }
    else
    {
        printf("wrong\n");
        exit(1);
        //prints error code if user doesn't only give one input
    }
         printf("\n");
}
