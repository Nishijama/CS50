
//Unfinished, I'm stuck at checksum

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int checksum(long number1);

int main (void)
{
long number = get_long("What's your card number?\n");

//here we should create and execute a checksum function

checksum(number);

if (number >= 340000000000000 && number < 350000000000000)
{
    printf("American Express\n");
}
else if (number >=	370000000000000 && number < 380000000000000)
{
    printf("American Express\n");
}
else if (number >=5100000000000000 && number < 5600000000000000)
{
    printf("MasterCard");
}
else if (number >=4000000000000000 && number < 5000000000000000)
{
    printf("Visa");
}

else
{
    printf("Invalid");
}
}

int checksum(long number1)
{
    float n1 = number1 % 10;
    float n2 = (int)(number1 * 0.1) % 10;
    float n3 = (int)(number1 * 0.01) % 10;
    float n4 = (int)(number1 * 0.001) % 10;
    float n5 = (int)(number1 * 0.0001) % 10;
    float n6 = (int)(number1 * 0.00001) % 10;
    float n7 = (int)(number1 * 0.000001) % 10;
    float n8 = (int)(number1 * 0.0000001) % 10;
    float n9 = (int)(number1 * 0.00000001) % 10;
    float n10 = (int)(number1 * 0.000000001) % 10;
    float n11 = (int)(number1 * 0.0000000001) % 10;
    float n12 = (int)(number1 * 0.00000000001) % 10;
    float n13 = (int)(number1 * 0.000000000001) % 10;
    float n14 = (int)(number1 * 0.0000000000001) % 10;
    float n15 = (int)(number1 * 0.00000000000001) % 10;

    int single = n1 + n3 + n3 + n5 + n7 + n9 + n11 + n13 + n15;
    int doubled = (n2 + n4 + n6 + n8 + n10 + n12 + n14) *2;

    printf ("single = %i", single);
    printf ("double = %i", doubled);

    //this is the final part of checksum
    if ((single + doubled) % 10 != 0)
    {
    printf("Invalid");
    return 1;
    }
    else {
        return 0;
    }
}