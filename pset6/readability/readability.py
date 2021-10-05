from cs50 import get_string

# get string from user
text = get_string("Put your text here: ")

# count letters, words and sentences
LetCount = 0
WordCount = 1
SentCount = 0
for i in range(len(text)):
    if text[i] >= 'a' and text[i] <= 'z' or text[i] >= 'A' and text[i] <= 'Z':
        LetCount += 1
    elif text[i] == ' ':
        WordCount += 1
    elif text[i] == '.' or text[i] == '?' or text[i] == '!':
        SentCount += 1

# Coleman-Liau index

L = LetCount * 100 / WordCount
S = SentCount * 100 / WordCount
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")