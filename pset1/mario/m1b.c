// this code is for a block of hashes

#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int steps = get_int("how many steps?\n");

    //this loop makes rows
    for (int j = 0; j < steps; j++)
    {
        //this loop makes columns
         for (int i = 0; i < steps; i++)
        {
            printf ("#");
        }
    printf ("#\n");
    }

    //This only puts the coursor at the new line
    printf ("\n");

}

// this is for left alligned pyramid

#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int steps = 0;

    //this loop gets height from the user
    while (steps > 10 || steps < 1)
    {
    steps = get_int("How many steps?\n");
    }

    //this loop makes rows
    for (int j = 0; j < steps; j++)
    {
        //this loop makes columns
         for (int i = 0; i < j; i++)
        {
            printf ("#");
        }
    printf ("#\n");
    }

    //This only puts the coursor at the new line
    printf ("\n");

}

//This is for creating pyramid with the dots but it's not working yet

#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int heigh = 0;

    //this loop gets height from the user
    while (heigh > 10 || heigh < 1)
    {
    heigh = get_int("How many steps?\n");
    }

    //this loop makes rows
    for (int row = 0; row < heigh; row++)
    {
        //this nested loop is supposed to make dots
         for (int dot = heigh; dot > 1; dot--)
        {
            printf (".");
        }
        //this nested loop makes hash pyramid
         for (int hash = 0; hash < row; hash++)
        {
            printf ("#");
        }
    printf ("#\n");
    }

    //This only puts the coursor at the new line
    printf ("\n");

}