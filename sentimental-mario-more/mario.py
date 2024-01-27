# TODO

while True:
    try:
        inp = int(input("Height: "))
        if inp > 0 and inp < 9:
            break
    except ValueError:
        print("", end="")

for i in range(1, inp+1):
    print(" " * (inp - i), end="")
    for j in range(i):
        print("#", end="")
    print("  ", end="")
    for j in range(i):
        print("#", end="")
    print()