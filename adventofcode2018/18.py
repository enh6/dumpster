with open('input18') as fp:
    area = [list(l.strip()) for l in fp]
n = len(area)
round = 0
round1, round2 = 10, 1000000000
found_loop = False
patterns = {}
while round < round2:
    next = []
    for y, row in enumerate(area):
        next_row = []
        for x, c in enumerate(row):
            adjacent = [(x + 1, y + 1), (x + 1, y), (x + 1, y - 1),
                    (x - 1, y + 1), (x - 1, y), (x - 1, y - 1),
                    (x, y + 1), (x, y - 1)]
            if c == '.':
                t = 0
                for x1, y1 in adjacent:
                    if x1 in range(n) and y1 in range(n) and area[y1][x1] == '|':
                        t += 1
                if t >= 3:
                    c = '|'
            elif c == '|':
                t = 0
                for x1, y1 in adjacent:
                    if x1 in range(n) and y1 in range(n) and area[y1][x1] == '#':
                        t += 1
                if t >= 3:
                    c = '#'
            else: # c == '#'
                t1, t2 = False, False
                for x1, y1 in adjacent:
                    if x1 in range(n) and y1 in range(n):
                        if area[y1][x1] == '#':
                            t1 = True
                        elif area[y1][x1] == '|':
                            t2 = True
                if not t1 or not t2:
                    c = '.'
            next_row.append(c)
        next.append(next_row)
    area = next
    round += 1

    if not found_loop:
        pattern = ''.join([''.join(row) for row in area])
        if pattern in patterns:
            found_loop = True
            loop_size = round - patterns[pattern]
            round = round2 - (round2 - round) % loop_size
        else:
            patterns[pattern] = round

    if round == round1 or round == round2:
        trees, lumberyards = 0, 0
        for row in area:
            lumberyards += row.count('#')
            trees += row.count('|')
        print(trees * lumberyards)

