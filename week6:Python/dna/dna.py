import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv)!=3:
        print("Usage:python dna.py databases/large(small).csv sequences/No.txt")
        return

    # TODO: Read database file into a variable
    with open(sys.argv[1],newline='') as f:
        reader=csv.reader(f)
        data=[]
        for row in reader:
            # {"albus":{"":15,"":},...}
            data.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2],'r') as f:
        seq=f.read()

    # TODO: Find longest match of each STR in DNA sequence
    match_str=[]
    for row in data[0]:
        match_str.append(longest_match(seq,row))

    # TODO: Check database for matching profiles
    f_out=0
    for i in range(1,len(data)):
        flag=1
        for j in range(1,len(match_str)):
            if match_str[j]!=int(data[i][j]):
                flag=0
                break
        if flag==1:
            print(data[i][0])
            f_out=1
    if f_out==0:
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
