#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)

{
    int q;
    int d;
    int n;
    int p;

    float change;
    do
    {
    change = get_float("How much change?\n");
    } while (change < 00.1);

    int cents = round(change * 100);
    printf("%i cents\n\n", cents);

    for (q=1; cents >=25; q++)
    {
        cents = cents -25;
        printf("wydano %i qarters \n", q);
        printf("do wydania zostalo %i \n\n", cents);
    }
    for (d=1; cents >=10; d++)
    {
        cents = cents -10;
        printf("wydano %i dime \n", d);
        printf("do wydania zostalo %i \n\n", cents);
    }
    for (n=1; cents >=5; n++)
    {
        cents = cents -5;
        printf("wydano %i nickles \n", n);
        printf("do wydania zostalo %i \n\n", cents);
    }
    for (p=1; cents >=1; p++)
    {
        cents = cents -1;
        printf("wydano %i pennies \n", p);
        printf("do wydania zostalo %i \n\n", cents);
    }
    int coins = q + d + n + p;
    printf("W sumie wydano %i \n", coins);

}