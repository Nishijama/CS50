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
       //  printf("Success\n");

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
       // printf("String value = %s, Int value = %i \n", k[1], val);
    }
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }


    string s = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') ||(s[i] >= 'A' && s[i] <= 'Z'))
        {
            printf("%c", s[i] + val);
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}