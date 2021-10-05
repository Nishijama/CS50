# TODO
import cs50, csv
from sys import argv, exit


# command line arguments
if len(argv) != 2:
    print("missing command-line argument")
    exit(1)

# Create empty file students.db
open(f"students.db", "w").close()

# Open the file for SQLite
db = cs50.SQL("sqlite:///students.db")

# Create table students in database students.db
db.execute("CREATE TABLE students('first' TEXT, 'middle' TEXT, 'last' TEXT, 'house' TEXT, 'birth' NUMERIC)")

# Open characters.csv
with open(argv[1], "r") as characters:

    # Create a reader
    reader = csv.DictReader(characters)

    first = "first"
    middle = "middle"
    last = "last"

    for row in reader:
        name = row["name"]
        house = row["house"]
        birth = row["birth"]

        splitnames = name.split()

        if len(splitnames) == 3:
            first = splitnames[0]
            middle = splitnames[1]
            last = splitnames[2]

        else:
            first = splitnames[0]
            middle = None
            last = splitnames[1]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
