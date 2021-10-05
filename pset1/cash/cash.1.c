#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)

{
    int q = 0, d = 0, n = 0, p = 0;

    float change;
    do
    {
        change = get_float("Change owed:\n");
    }
    //For some reason, 0.01 was not accepted, so had to decrease the condition here
    while (change < 0.009 || change > 10);

    int cents = round(change * 100);

    printf("Return: ");
    if (cents >= 25)
    {
        q = cents / 25;
        cents = cents % 25;
        printf("%i quarters, ", q);
    }
    if (cents >= 10)
    {
        d = cents / 10;
        cents = cents % 10;
        printf("%i dimes, ", d);
    }
    if (cents >= 5)
    {
        n = cents / 5;
        cents = cents % 5;
        printf("%i nickles, ", n);
    }
    if (cents >= 1)
    {
        p = cents / 1;
        cents = cents % 1;
        printf("%i pennies\n", p);
    }
    int coins = q + d + n + p;
    printf("In total %i coins\n", coins);
}