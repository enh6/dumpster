x, y, v = [], [], []
with open('input10') as fp:
    for l in fp:
        x.append(int(l[10:16]))
        y.append(int(l[18:24]))
        v.append((int(l[36:38]), int(l[40:42])))

w = 80
h = 30
t = 0

#for i in range(len(x)):
#    x[i] += v[i][0] * 10000
#    y[i] += v[i][1] * 10000
#t += 10000

while True:
    t += 1
    for i in range(len(x)):
        x[i] += v[i][0]
        y[i] += v[i][1]
    if max(x) - min(x) < w and max(y) - min(y) < h:
        bitmap = [[' '] * w for i in range(h)]
        for i in range(len(x)):
            bitmap[y[i] - min(y)][x[i] - min(x)] = '#'
        print(t)
        print('\n'.join([''.join(l) for l in bitmap]))
        if input() == 'q':
            break

