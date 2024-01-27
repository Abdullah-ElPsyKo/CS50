# TODO

def main():
    text = input("Text: ")
    length = len(text)

    if length == 0:
        return 1

    letters = 0
    sentences = 0
    words = 1  # count the first word

    for i in range(length):
        if text[i] == ' ':
            words += 1
        elif ((text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z')):
            letters += 1
        elif (text[i] == '!' or text[i] == '.' or text[i] == '?'):
            sentences += 1

    index = round(0.0588 * (letters / words * 100.0) - 0.296 * (sentences / words * 100.0) - 15.8)

    if (index < 16 and index >= 1):
        print(f"Grade {index}")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade 16+")


main()