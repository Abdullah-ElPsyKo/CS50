#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int main(void)
{
    string text = get_string("Text: ");
    int textLen = strlen(text);

    int letters = 0;
    if (textLen == 0)
    {
        return 1;
    }
    int words = 1;
    int sentences = 0;

    int index;
    printf("\n");
    for (int i = 0; i < textLen; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
        else if ((text[i] >= 97 && text[i] <= 122) || (text[i] >= 65 && text[i] <= 90))
        {
            letters++;
        }
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
        }
    }

    index = round(0.0588 * (letters / (double)words * 100.0) - 0.296 * (sentences / (double)words * 100.0) - 15.8);
    if (index < 16 && index >= 1)
    {
        printf("Grade %i\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}