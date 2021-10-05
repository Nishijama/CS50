#include <stdio.h>
#include <cs50.h>


int height = 0;

void pyramid(void);

int main(void)


{
    while (height > 8 || height < 1)
    {
        height = get_int("How many steps(1-8)?\n");
    }
    pyramid();
}




void pyramid(void)
{
    //this loop makes rows
    for (int row = 0; row < height; row++)
    {

        //this loop is responsible for right alligning the left side of the pyramid
        for (int dot = height - 1; dot > row; dot --)
        {
            printf(" ");
        }

        //this creates the left side of the pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }
        printf("#  ");

        // this loop creates right side of the pyramid
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }

        printf("#\n");
    }
}

