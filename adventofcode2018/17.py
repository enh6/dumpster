import re

inputs = []
maxx, minx = 0, 1000
maxy, miny = 0, 1000
with open('input17') as fp:
    for l in fp:
        l = [l[0]] + [int(n) for n in re.findall('\d+', l)]
        inputs.append(l)
        if l[0] == 'x':
            if l[1] > maxx:
                maxx = l[1]
            if l[1] < minx:
                minx = l[1]
            if l[2] < miny:
                miny = l[2]
            if l[3] > maxy:
                maxy = l[3]
        else: # l[0] == 'y'
            if l[1] > maxy:
                maxy = l[1]
            if l[1] < miny:
                miny = l[1]
            if l[2] < minx:
                minx = l[2]
            if l[3] > maxx:
                maxx = l[2]

bitmap = [['.'] * (maxx - minx + 3) for i in range(maxy - miny + 2)]
for l in inputs:
    if l[0] == 'x':
        x = l[1]
        for y in range(l[2], l[3] + 1):
            bitmap[y - miny + 1][x - minx + 1] = '#'
    else:
        y = l[1]
        for x in range(l[2], l[3] + 1):
            bitmap[y - miny + 1][x - minx + 1] = '#'

waters = set()
waters.add((500 - minx + 1, 0))
bitmap[0][500 - minx + 1] = '+'

while waters:
    x, y = waters.pop()
    #flow down
    while y < maxy - miny + 1 and bitmap[y + 1][x] == '.':
        bitmap[y + 1][x] = '|'
        y += 1
    if y < maxy - miny + 1 and (bitmap[y + 1][x] == '#' or
            bitmap[y + 1][x] == '~'):
        # flow left
        x1 = x
        while x1 > 0 and (bitmap[y][x1 - 1] == '.' or
                bitmap[y][x1 - 1] == '|'):
            bitmap[y][x1 - 1] = '|'
            if bitmap[y + 1][x1 - 1] == '.':
                waters.add((x1 - 1, y))
                break
            elif bitmap[y + 1][x1 - 1] == '|':
                break
            else:
                x1 -= 1
        # detect reservoir when see # on left
        if x1 > 0 and bitmap[y][x1 - 1] == '#':
            while x1 + 1 <= maxx and bitmap[y][x1 + 1] == '|':
                x1 += 1
            # found reservoir
            if bitmap[y][x1 + 1] == '#':
                while x1 >= 0 and bitmap[y][x1] == '|':
                    bitmap[y][x1] = '~'
                    if bitmap[y - 1][x1] == '|':
                        waters.add((x1, y - 1))
                    x1 -= 1
        # flow right
        x2 = x
        while x2 < maxx and (bitmap[y][x2 + 1] == '.' or
                bitmap[y][x2 + 1] == '|'):
            bitmap[y][x2 + 1] = '|'
            if bitmap[y + 1][x2 + 1] == '.':
                waters.add((x2 + 1, y))
                break
            elif bitmap[y + 1][x2 + 1] == '|':
                break
            else:
                x2 += 1
        # detect reservoir when see # on right
        if x2 < maxx and bitmap[y][x2 + 1] == '#':
            while x2 - 1 >= 0 and bitmap[y][x2 - 1] == '|':
                x2 -= 1
            # found reservoir
            if bitmap[y][x2 - 1] == '#':
                while x2 <= maxx and bitmap[y][x2] == '|':
                    bitmap[y][x2] = '~'
                    if bitmap[y - 1][x2] == '|':
                        waters.add((x2, y - 1))
                    x2 += 1

ans1, ans2 = 0, 0
for row in bitmap:
    for c in row:
        if c == '|' or c == '~':
            ans1 += 1
        if c == '~':
            ans2 += 1
print(ans1, ans2)
