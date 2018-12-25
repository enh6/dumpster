with open('input22') as fp:
    depth = int(fp.readline().strip()[7:])
    target = fp.readline().strip()[8:].split(',')
    target_x, target_y = int(target[0]), int(target[1])

risk = 0
cave = [[0] * (target_x + 1) for i in range(target_y + 1)]
for y in range(target_y + 1):
    for x in range(target_x + 1):
        if (x, y) == (0, 0) or (x, y) == (target_x, target_y):
            idx = 0
        elif y == 0:
            idx = x * 16807
        elif x == 0:
            idx = y * 48271
        else:
            idx = cave[y - 1][x] * cave[y][x - 1]
        cave[y][x] = (idx + depth) % 20183
        risk += cave[y][x] % 3
print(risk)

# part two
types = ['rocky', 'wet', 'narrow']
tools = {'rocky': ('climb', 'torch'),
        'wet': ('climb', 'none'),
        'narrow': ('torch', 'none')}
# if padding is too small, the result will be wrong
# if padding is too large, execution time will be too long
padding = 20
cave = [[0] * (target_x + padding) for i in range(target_y + padding)]
cave2 = {}
for y in range(target_y + padding):
    for x in range(target_x + padding):
        if (x, y) == (0, 0) or (x, y) == (target_x, target_y):
            idx = 0
        elif y == 0:
            idx = x * 16807
        elif x == 0:
            idx = y * 48271
        else:
            idx = cave[y - 1][x] * cave[y][x - 1]
        cave[y][x] = (idx + depth) % 20183
        mod = cave[y][x] % 3
        type = types[mod]
        cave2[(x, y)] = {'type': type, tools[type][0]: 99999, tools[type][1]: 99999}
cave2[(0, 0)]['torch'] = 0

from heapq import heappop, heappush
heap = []
heappush(heap, (0, 0, 0, 'torch'))
closed = set()
while heap:
    (_, x, y, tool) = heappop(heap)
    if (x, y) == (target_x, target_y):
        break
    if (x, y, tool) in closed:
        continue
    closed.add((x, y, tool))

    r = cave2[(x, y)]
    type = r['type']
    (t1, t2) = tools[type]
    if tool == t1 and r[t1] + 7 < r[t2]:
        r[t2] = r[t1] + 7
        heappush(heap, (r[t2], x, y, t2))
    elif tool == t2 and r[t2] + 7 < r[t1]:
        r[t1] = r[t2] + 7
        heappush(heap, (r[t1], x, y, t1))

    for x2, y2 in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
        if x2 in range(0, target_x + padding) and y2 in range(0, target_y + padding):
            r2 = cave2[(x2, y2)]
            type2 = r2['type']
            if type2 == type:
                for tool in tools[type]:
                    if tool in r and r[tool] + 1 < r2[tool]:
                        r2[tool] = r[tool] + 1
                        heappush(heap, (r2[tool], x2, y2, tool))
            else:
                tool = set(tools[type]) & set(tools[type2])
                tool = tool.pop()
                if r[tool] + 1 < r2[tool]:
                    r2[tool] = r[tool] + 1
                    heappush(heap, (r2[tool], x2, y2, tool))

print(cave2[(target_x, target_y)]['torch'])
