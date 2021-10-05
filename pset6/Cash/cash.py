# cash.py
from cs50 import get_float

dollars = 0

while float(dollars) < 0.01 or dollars > 100:
    dollars = get_float("Change owed: ")

cents = round(dollars * 100)

# print(f"it's {cents} cents")
# quarter = 25 cents, dime = 10 cents, nickle = 5 cents, penny = 1 cent

q = 0
d = 0
n = 0
p = 0

if cents >= 25:
    q = int(cents / 25)
    cents = cents % 25

if cents >= 10:
    d = int(cents / 10)
    cents = cents % 10

if cents >= 5:
    n = int(cents / 5)
    cents = cents % 5

p = cents

# print(f"That's {q} quarters, {d} dimes, {n} nickles, {p} pennies")
print(f"That's {q+d+n+p} coints in total")