#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int n = get_int("gimme number\n");
    int x = get_int("divided by: \n");
    printf ("%i divided by %i gives %i, remainder is %i\n", n, x, n/x, n%x);
}