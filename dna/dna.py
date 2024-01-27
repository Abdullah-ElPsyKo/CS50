import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("usage: python.py [fileName] [fileName]")
        return 1
    # TODO: Read database file into a variable
    allDna = []
    with open(sys.argv[1], "r") as dbF:
        reader = csv.DictReader(dbF)
        for row in reader:
            allDna.append(row)
    # TODO: Read DNA sequence file into a variable
    dna = ""
    with open(sys.argv[2], "r") as dnaSeq:
        dna = dnaSeq.read()
    # TODO: Find longest match of each STR in DNA sequence
    # count DNA sequences
    cAGATC = 0
    cAATG = 0
    cTATC = 0
    cAGATC += longest_match(dna, "AGATC")
    cAATG += longest_match(dna, "AATG")
    cTATC += longest_match(dna, "TATC")
    # TODO: Check database for matching profiles
    for i in range(len(allDna)):
        if (int(allDna[i]["AGATC"]) == cAGATC and int(allDna[i]["AATG"]) == cAATG and int(allDna[i]["TATC"]) == cTATC):
            print(allDna[i]["name"])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
