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
        string k = argv[1];
        int l = strlen(k);
        int m = strlen(k);
        int p = 0;
        
        for (int q = 0; q < l; q++)
        {
            if isalpha(k[q])
            {
                
            }
            else
            {
              printf("error: can only have letters in key\n");
                exit(1);  
            }
        }
                {
            //converts argv[1] into a string separated in a variable
            printf("plaintext:");
               string plaintext = get_string();
               //asks user for a plaintext input
               printf("ciphertext:");
                    for (int i = 0, n = strlen(plaintext); i < n; i++)
                    if isalpha(plaintext[i])
                    //checks if alphabetic character
                        {
                            if isupper(k[l%m])
                            {
                                p = k[l%m] - 65;
                    //converts uppercase input to alphabetic and back to ASCII
                            }
                            else
                            {
                                p = k[l%m] - 97;
                    //converts lowercase input to alphabetic and back to ASCII
                            }
                            if isupper(plaintext[i])
                            {
                                printf("%c", ((plaintext[i]-65+p)%26)+65);
                                l += 1;
                                // converts text into code using equation
                            }
                            if islower(plaintext[i])
                            {
                                printf("%c", ((plaintext[i]-97+p)%26)+97);
                                l += 1;
                                // converts text into code using equation
                            }
                        }
                    else
                        {
                        printf("%c", plaintext[i]);
                        //outputs text if it's not an alphabetic character
                        }
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
