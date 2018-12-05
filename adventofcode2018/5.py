polymer = []
with open('input5') as fp:
    for c in fp.read().strip('\n'):
        n = ord(c)
        if polymer and abs(polymer[-1] - n) == 32:
            polymer.pop()
        else:
            polymer.append(n)
print(len(polymer))

min_len = len(polymer)
for i in range(65, 65 + 26):
    poly = [n for n in polymer if n != i and n != 32 + i]
    stack = []
    for n in poly:
        if stack and abs(stack[-1] - n) == 32:
            stack.pop()
        else:
            stack.append(n)
    if len(stack) < min_len:
        min_len = len(stack)
print(min_len)
