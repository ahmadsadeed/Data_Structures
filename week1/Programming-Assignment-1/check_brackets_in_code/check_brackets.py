# python3

from collections import namedtuple

Bracket = namedtuple("Bracket", ["char", "position"])


def are_matching(left, right):
    return (left + right) in ["()", "[]", "{}"]


def find_mismatch(text):
    opening_brackets_stack = []
    for i, char in enumerate(text):
        if char in "([{":
            opening_brackets_stack.append(Bracket(char, i+1))

        if char in ")]}":
            if len(opening_brackets_stack) == 0:
                opening_brackets_stack.append(Bracket(char, i+1))
                break
            b = opening_brackets_stack[-1]
            if are_matching(b.char, char):
                opening_brackets_stack.pop()
            else:
                opening_brackets_stack.append(Bracket(char, i+1))
                break
    if len(opening_brackets_stack) == 0:
        return "Success"
    else:
        return opening_brackets_stack[-1].position


def main():
    text = input()
    mismatch = find_mismatch(text)
    # Printing answer, write your code here
    print(mismatch)


if __name__ == "__main__":
    main()
