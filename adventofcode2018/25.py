points = []
with open('input25') as fp:
    for l in fp:
        points.append([int(n) for n in l.split(',')])

def dist(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]) + abs(a[3] - b[3])

constellations = []
for i, point in enumerate(points):
    constellation = [i]
    for j, c in enumerate(constellations):
        for idx in c:
            if dist(point, points[idx]) <= 3:
                constellation += c
                constellations[j] = []
                break
    constellations.append(constellation)
print([len(c) > 0 for c in constellations].count(True))



