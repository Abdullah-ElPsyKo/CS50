#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool checkValidityArg(string arg);

int main(int argc, string argv[])
{
    if (argc != 2 || checkValidityArg(argv[1]) == false) //check if every charachter is valid
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    int key = atoi(argv[1]); //convert to integer
    char l;
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        //check for lowercase/uppercase/other chars
        if (plaintext[i] <= 'z' && plaintext[i] >= 'a')
        {
            l = 'a';
        }
        else if (plaintext[i] <= 'Z' && plaintext[i] >= 'A')
        {
            l = 'A';
        }
        else
        {
            printf("%c", plaintext[i]);
            continue;
        }
        char position = plaintext[i] - l;
        char letter = ((position + key) % 26) + l;
        printf("%c", letter);
    }
    printf("\n");
}
bool checkValidityArg(string arg)
{
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}