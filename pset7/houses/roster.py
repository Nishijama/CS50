# TODO
# TODO
import cs50
from sys import argv, exit

# command line arguments
if len(argv) != 2:
    print("missing command-line argument")
    exit(1)

file = open("students.db", "r")
db = cs50.SQL("sqlite:///students.db")

dictlist = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house = '{argv[1]}' ORDER BY last ASC, first ASC")

for i in range(0, len(dictlist)):
    if dictlist[i]['middle'] != None:
        print(f"{dictlist[i]['first']} {dictlist[i]['middle']} {dictlist[i]['last']}, born {dictlist[i]['birth']}")
    else:
        print(f"{dictlist[i]['first']} {dictlist[i]['last']}, born {dictlist[i]['birth']}")