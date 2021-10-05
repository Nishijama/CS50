#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("Put your text here: ");

    //Count Letters
    float LetCount = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            LetCount++;
            //printf("%c", s[i]);
        }
    }
    //printf("Letter(s): %i\n", LetCount);

    //Count words
    float WordCount = 1;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            WordCount++;
        }
    }
    //printf("Word(s): %i\n", WordCount);

    //Count sentences
    float SentCount = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            SentCount++;
        }
    }
    //printf("Sentence(s): %i\n", SentCount);

    //Index
    float L = LetCount * 100 / WordCount;
    float S = SentCount * 100 / WordCount;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }


}