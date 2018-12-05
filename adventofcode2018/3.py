import sys, re

# get rect info from input
rects = []
with open('input3') as fp:
    for l in fp:
        rects.append([int(n) for n in re.findall('\d+', l)])

# first puzzle
bitmap = [[0] * 1000 for i in range(1000)]
num = 0
for rect in rects:
    for x in range(rect[1], rect[1] + rect[3]):
        for y in range(rect[2], rect[2] + rect[4]):
            if bitmap[x][y] == 1:
                num += 1
            bitmap[x][y] += 1
print(num)

# second puzzle
for rect in rects:
    overlap = False
    for x in range(rect[1], rect[1] + rect[3]):
        for y in range(rect[2], rect[2] + rect[4]):
            if bitmap[x][y] != 1:
                overlap = True
    if not overlap:
        print(rect[0])
        sys.exit()
