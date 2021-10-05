#include <stdio.h>
#include <cs50.h>

void pyramid(int h);

int main(void)
{
    int height = 0;
    //this loop gets height from the user
    while (height > 8 || height < 1)
    {
        height = get_int("How many steps (1-8)?\n");
    }
    pyramid(height);
}

void pyramid(int h)
{
    //this loop makes rows
    for (int row = 1; row <= h; row++)
    {
        for (int dot = h; dot > row; dot --)
        {
            printf(" ");
        }
        //this nested loop prints hashes
        for (int hash = 1; hash <= row; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}