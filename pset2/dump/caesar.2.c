#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]);
       // printf("hello, %s\n", argv[1]);
       printf("Input your message:")
       string plaintext = get_string();
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                if isalpha(plaintext[i])
                {
                    if isupper(plaintext[i])
                    {
                        //change ascii to right place and proint that 
                        if plaintext[i]=='89'
                        {
                            printf('65');
                        }
                        if plaintext[i]=='90'
                        {
                            printf('66');
                        }
                        else
                        {
                        printf("%c+2\n", plaintext[i]);
                        }
                    }
                    else
                    {
                        //change ascii to lowercase and print that
                        printf("%c+2\n", plaintext[i]);
                    }

                }
            }
    }
    else
    {
        printf("wrong\n");
    }
}

// string num = "50";
// int i = atoi(num);