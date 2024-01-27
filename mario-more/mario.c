#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    for (int i = 0; i < height; i++)
    {
        int whiteSpace = height - i;
        for (int j = 0; j < whiteSpace - 1; j++) //correct amount of spaces
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  "); //2 hash spaces inbetween
        for (int n = 0; n < i + 1; n++)
        {
            printf("#");
        }
        printf("\n");
    }
}