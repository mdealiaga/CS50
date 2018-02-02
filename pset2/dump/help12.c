#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int vigenereUpper(char input, char k);
int vigenereLower(char input, char k);

int main(int argc, string argv[])
{
    // Check if there are 2 command line inputs
    if (argc != 2)
    {
        // Print Error message if not 2 inputs
        printf("Error\n");
        return 1;
    }
    else
    {
        // Store argv[1] in variable key
        string key = argv[1];
        
        // Vigenere cipher for uppercase letters
int vigenereUpper(char input, char k)
{
    int value = (((int) input - 65 + ((int) k - 65)) % 26) + 65;
    return (char) value;
}

//Vigenere cipher for lowercase letters
int vigenereLower(char input, char k)
{
    int value = (((int) input - 97 + ((int) k - 97)) % 26) + 97;
    return (char) value;
}
        // Loop through each character in argv[1]
        for(int i = 0, n = strlen(key); i < n; i++ )
        {
            // Check if character is alphabetical
            if (isalpha(key[i]) == 0)
            {
                // Print Error if character not alphabetical
                printf("ERROR\n");
                return 1;
            }
        }
        printf("plaintext: ");
        // Get plaintext, store in variable ptext
        string ptext = get_string();
        printf("ciphertext: ");
        // Loop through each character of plaintext
        for (int i = 0, n = strlen(ptext); i < n; i++)
        {
            // Check if character is a letter
            if (isalpha(ptext[i]))
            {
                // Check if charater is uppercase
                if (isupper(ptext[i]))
                {
                    // Loop through each character in key
                    for (int j = 0, m = strlen(key); j < m; j++)
                    {
                        // Implement Vigenere cipher (below)
                        printf("%c", vigenereUpper(ptext[i], key[j]));
                    }
                }
                // Check if character is lowercase
                else if (islower(ptext[i]))
                {
                    // Loop through each character in key
                    for (int j = 0, m = strlen(key); j < m; j++)
                    {
                        // Implement Vigenere cipher (below)
                        printf("%c", vigenereLower(ptext[i], key[j]));
                    }
                }
            }
            else
            {
                // Print character if not letter (spaces, periods, etc.)
                printf("%c", ptext[i]);
            }
        }
    }
    // Print new line
    printf("\n");
    return 0;
}

