//caesar

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string k[])
{
    //get string from command-line argument
    int val;
    if (argc == 2)
    {
        string key = k[1];

        // check if argument cointains only digits
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            //if it's not a digit
            if (isdigit(key[i]) == 0)
            {
                printf("Usage: ./caesar key");
                return 1;
            }
        }

        // convert string to int
        val = atoi(key);
    }
    else
    {
        //if the command-line argument is wrong
        printf("Usage: ./caesar key");
        return 1;
    }

// ciphering

    string s = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if it's a letter
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            // how to loop from z to a?
            if ((s[i] + val) > 122)
            {
                int x = (s[i]) + val;
                int y = x % 122;
                if (y > 26)
                {
                    printf("%c", 96 + y % 26);
                }
                else
                {
                    printf("%c", 96 + y);
                }
                // how to loop from Z to A?
            }
            else if ((s[i] + val) > 90 && (s[i] + val) < 97)
            {
                int x1 = (s[i]) + val;
                int y1 = x1 % 90;
                if (y1 > 26)
                {
                    printf("%c", 64 + y1 % 26);
                }
                else
                {
                    printf("%c", 64 + y1);
                }
            }
            //how to print when no looping is necesarry?
            else
            {
                printf("%c", s[i] + val);
            }
        }
        //if it's not a letter
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}