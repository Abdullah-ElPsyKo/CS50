#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("name: ");
    printf("hello, %s\n", name);
}