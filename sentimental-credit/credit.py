# TODO

def main():
    n = input("Number: ")
    numDigits = len(n)
    number = int(n)

    odd = 0
    even = 0
    digit = 0

    for i in range(numDigits):
        if i % 2 != 0:
            digit = (number % 10) * 2
            if digit > 9:
                odd += digit - 9
            else:
                odd += digit
        else:
            even += (number % 10)

        number //= 10

    sum = odd + even

    if sum % 10 == 0:
        firstTwo = int(n[0] + n[1])
        first = int(n[0])
        if (firstTwo >= 51) and (firstTwo <= 55):
            print("MASTERCARD")
        elif (first == 4) and (numDigits == 13 or numDigits == 16):
            print("VISA")
        elif (firstTwo == 34 or firstTwo == 37) and (numDigits == 15):
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()