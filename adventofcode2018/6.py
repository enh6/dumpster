# get coordinates from input
x, y = [], []
with open('input6') as fp:
    for l in fp:
        xy = l.split(',')
        x.append(int(xy[0]))
        y.append(int(xy[1]))

x = [i - min(x) for i in x]
y = [i - min(y) for i in y]
maxx = max(x)
maxy = max(y)

# naive solution for part one. too slow.
#area = [0] * len(x)
#for i in range(maxx + 1):
#    for j in range(maxy + 1):
#        min_dist = 1000
#        idx = 0
#        for k in range(len(x)):
#            dist = abs(x[k] - i) + abs(y[k] - j)
#            if dist < min_dist:
#                min_dist = dist
#                idx = k
#            elif dist == min_dist:
#                idx = -1
#        if idx != -1:
#            if area[idx] != -1:
#                area[idx] += 1
#            if i == 0 or i == maxx or j == 0 or j == maxy:
#                area[idx] = -1
#print(max(area))

# part one
area1 = [1] * len(x)
bitmap = [[0] * (maxy + 1) for i in range(maxx + 1)]
points = {}
for i in range(len(x)):
    points[(x[i], y[i])] = i
    bitmap[x[i]][y[i]] = 1
while points:
    new_points = {}
    for (px, py), idx in points.items():
        if px - 1 >= 0 and bitmap[px - 1][py] == 0:
            if (px - 1, py) not in new_points:
                new_points[(px - 1, py)] = idx
            elif new_points[(px - 1, py)] != idx:
                new_points[(px - 1, py)] = -1
        if px + 1 <= maxx and bitmap[px + 1][py] == 0:
            if (px + 1, py) not in new_points:
                new_points[(px + 1, py)] = idx
            elif new_points[(px + 1, py)] != idx:
                new_points[(px + 1, py)] = -1
        if py - 1 >= 0 and bitmap[px][py - 1] == 0:
            if (px, py - 1) not in new_points:
                new_points[(px, py - 1)] = idx
            elif new_points[(px, py - 1)] != idx:
                new_points[(px, py - 1)] = -1
        if py + 1 <= maxy and bitmap[px][py + 1] == 0:
            if (px, py + 1) not in new_points:
                new_points[(px, py + 1)] = idx
            elif new_points[(px, py + 1)] != idx:
                new_points[(px, py + 1)] = -1
    for (px, py), idx in new_points.items():
        bitmap[px][py] = 1
        if idx != -1:
            if px == 0 or px == maxx or py == 0 or py == maxy:
                area1[idx] = -1
            elif area1[idx] != -1:
                area1[idx] += 1
    points = new_points
print(max(area1))

# part two
sumx = []
for i in range(maxx + 1):
    sumx.append(sum([abs(xx - i) for xx in x]))
sumy = []
for i in range(maxy + 1):
    sumy.append(sum([abs(yy - i) for yy in y]))
area2 = 0
for i in sumx:
    for j in sumy:
        if i == 0 or i == maxx or j == 0 or j == maxy:
            assert i + j >= 10000
        if i + j < 10000:
            area2 += 1
print(area2)
