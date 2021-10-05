# python mario.py

from cs50 import get_int

number = 0

# ask for number from 1 to 8
while number not in range(1, 9):
    number = get_int("Please gimme number\n")

# make a pyramid
for i in range(1, number+1):

    # print spaces
    j = number
    while j > i:
        print(" ", end="")
        j = j - 1
    # print hashes
    for k in range(i):
        print("#", end="")

    # print new line
    print("\n", end="")

