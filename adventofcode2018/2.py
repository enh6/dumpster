import sys

# load input strings to a list
with open('input2') as fp:
    lines = [l.rstrip('\n') for l in fp]

# first puzzle
twos = 0
threes = 0

for line in lines:
    chars = {}
    for c in line:
        chars[c] = chars.get(c, 0) + 1
    if 2 in chars.values():
        twos += 1
    if 3 in chars.values():
        threes += 1
print(twos * threes)

# second puzzle
for l1 in lines:
    for l2 in lines:
        diff = 0
        pos = 0
        for i in range(len(l1)):
            if l1[i] != l2[i]:
                diff += 1
                pos = i
                if diff > 1:
                    break
        if diff == 1:
            print(l1[:pos] + l1[pos + 1:])
            sys.exit()
