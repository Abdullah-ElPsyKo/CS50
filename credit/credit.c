#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    long n = get_long("Number: ");
    long temp = n;
    int odd = 0;
    int even = 0;
    int digit;
    int numDigits = 0;
    long t = n;
    while (t > 0)
    {
        t /= 10;
        numDigits++;
    }
    int firstNumber;
    int secondNumber;
    for (int i = 0; i < numDigits; i++)
    {
        if (i == (numDigits - 1))
        {
            firstNumber = (temp % 10);
        }
        if (i == (numDigits - 2))
        {
            secondNumber = (temp % 10);
        }

        if (i % 2 != 0)
        {
            digit = (temp % 10) * 2;
            if (digit > 9)
            {
                odd += digit - 9;
            }
            else
            {
                odd += digit;
            }
        }
        else
        {
            even += (temp % 10);
        }

        temp /= 10;
    }
    int sum = odd + even;
    if (sum % 10 == 0)
    {
        if (firstNumber == 5 && (secondNumber >= 1 && secondNumber <= 5))
        {
            printf("MASTERCARD\n");
        }
        else if (firstNumber == 4 && (numDigits == 13 || numDigits == 16))
        {
            printf("VISA\n");
        }
        else if (firstNumber == 3 && (secondNumber == 4 || secondNumber == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}