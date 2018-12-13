# calculate power levels
serial = 2568
w, h = 300, 300
cells = []
for y in range(1, h + 1):
    cells.append([])
    for x in range(1, w + 1):
        rack = x + 10
        power = (rack * y + serial) * rack
        cells[-1].append(power // 100 % 10 - 5)

# part one
max = -100
for y in range(h - 2):
    for x in range(w - 2):
        total = sum(cells[y + 0][x:x + 3] + cells[y + 1][x:x + 3] +
                cells[y + 2][x:x + 3])
        if total > max:
            max = total
            maxx, maxy = x, y
print(maxx + 1, maxy + 1)

# part two
sums = []
for y in range(h):
    sums.append([])
    row = 0
    for x in range(w):
        row += cells[y][x]
        if y:
            sums[-1].append(sums[y - 1][x] + row)
        else:
            sums[-1].append(row)

for y in range(h):
    for x in range(w):
        for n in range(1, min(h - y, w - x)):
            if x and y:
                total = (sums[y + n - 1][x + n - 1] + sums[y - 1][x - 1] -
                        sums[y + n - 1][x - 1] - sums[y - 1][x + n - 1])
            else:
                total = sums[y][x]
            if total > max:
                max = total
                maxx, maxy, maxn = x, y, n
print(maxx + 1, maxy + 1, maxn)





