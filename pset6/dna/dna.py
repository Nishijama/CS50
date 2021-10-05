import csv
from sys import argv, exit

if len(argv) != 3:
    print("missing command-line argument(s)")
    exit(1)

# Open STR database
with open(argv[1], "rt") as STRdata, open(argv[2], "r") as sequence_file:

    # Create reader for STRs
    reader = csv.DictReader(STRdata)

    # Get STRs from csv file
    STRs = reader.fieldnames

    sequence = sequence_file.read()
    STRcountDict = {}

    for STRno in range(1, len(STRs)):
        # for AGAT in range AGAT, TTTTC, AATG

        # create STR counters for each STR
        STRcounter = 0
        subcounter = 0
        # go through every character in sequence and check following X characters if together they form the STR in question
        for i in range(len(sequence)):

            # when you find the first STR occurence:
            if sequence[i:i+len(STRs[STRno])] == STRs[STRno]:

                # Compute how many times it appears in sequence afterwards - check the next substrings
                j = i

                while j < len(sequence):
                    if sequence[j:j+len(STRs[STRno])] == STRs[STRno]:
                        subcounter += 1
                        j = j + len(STRs[STRno])

                    else:
                        if subcounter > STRcounter:
                            STRcounter = subcounter
                        subcounter = 0

                        break

        STRcountDict.update({STRs[STRno]: STRcounter})

    # print count of found strings
    # check the results against the database and print
    for row in reader:
        counter = 0

        for STRno in range(1, len(STRs)):
            if int(row[STRs[STRno]]) == int(STRcountDict[STRs[STRno]]):
                counter += 1

        if counter == len(STRs)-1:
            print(row["name"])
            exit(0)
    print("No match")