from copy import deepcopy
from collections import defaultdict

with open('input15') as fp:
    inputs = [list(l.strip()) for l in fp]

def generateMap():
    global map, units
    map = deepcopy(inputs)
    units = []
    for y, row in enumerate(map):
        for x, c in enumerate(row):
            if c in 'EG':
                unit = [x, y, c, 200]
                row[x] = unit
                units.append(unit)

def findNeighbourTargets(u):
    target = None
    x, y, t, hp = u
    if t in 'EG':
        for x2, y2 in [(x, y - 1), (x - 1, y), (x + 1, y), (x, y + 1)]:
            u2 = map[y2][x2]
            if type(u2) is list and u2[2] != t:
                if not target:
                    target = u2
                elif u2[3] < target[3]:
                    target = u2
    return target

def attack(target, ap):
    target[3] -= ap
    if target[3] <= 0:
        map[target[1]][target[0]] = '.'

def move(u):
    closed = {}
    cur = {(u[0], u[1]) : []}
    found = defaultdict(list)
    while cur:
        # expand cur for one step
        # move cur to closed
        # if cur is empty and no target found, do nothing
        next = defaultdict(list)
        for (x, y), prev in cur.items():
            for x2, y2 in [(x, y - 1), (x - 1, y), (x + 1, y), (x, y + 1)]:
                u2 = map[y2][x2]
                if u2 == '.':
                    if (x2, y2) in closed or (x2, y2) in cur:
                        pass
                    else:
                        next[(x2, y2)].append((x, y))
                # found target
                elif type(u2) is list and u2[2] != u[2]:
                    found[(x2, y2)].append((x, y))
        for k, v in cur.items():
            closed[k] = v
            cur = next

        if not found:
            continue

        # if found multiple targets, choose the upper left one
        target = None
        for (x, y), prev in found.items():
            if not target or y < target[1] or (y == target[1] and
                    x < target[0]):
                target = (x, y, prev)

        # backtrack from target to original position
        cur = {(target[0], target[1]): target[2]}
        while True:
            next = {}
            for pos, prevs in cur.items():
                # prev is original position, move and return
                if prevs == [(u[0], u[1])]:
                    tar = None
                    for t2 in cur:
                        if not tar or t2[1] < tar[1] or (t2[1] == tar[1] and
                                t2[0] < tar[0]):
                            tar = (t2[0], t2[1])
                    map[tar[1]][tar[0]] = u
                    map[u[1]][u[0]] = '.'
                    u[0], u[1] = tar[0], tar[1]
                    return
                for p in prevs:
                    if p not in next:
                        next[p] = closed[p]
            cur = next

def combatEnds():
    for u in units:
        if u[3] > 0:
            t = u[2]
            break
    for u in units:
        if u[2] != t and u[3] > 0:
            return False
    return True

def partOne():
    generateMap()
    end = False
    round = 0
    while True:
        units.sort(key = lambda u : u[1] * 1000 + u[0])
        for u in units:
            if end:
                hp = sum([u[3] for u in units if u[3] > 0])
                print(round * hp)
                return
            if u[3] <= 0: # ignore dead units
                continue
            target = findNeighbourTargets(u)
            if not target:
                move(u)
                target = findNeighbourTargets(u)
            if target:
                attack(target, 3)
                end = combatEnds()
        round += 1

def partTwo(elf_ap):
    generateMap()
    end = False
    round = 0
    while True:
        units.sort(key = lambda u : u[1] * 1000 + u[0])
        for u in units:
            if end:
                for u in units:
                    if u[2] == 'E' and u[3] <= 0:
                        return False
                hp = sum([u[3] for u in units if u[3] > 0])
                print(round * hp)
                return True
            if u[3] <= 0: # ignore dead units
                continue
            target = findNeighbourTargets(u)
            if not target:
                move(u)
                target = findNeighbourTargets(u)
            if target:
                if u[2] == 'E':
                    attack(target, elf_ap)
                else:
                    attack(target, 3)
                end = combatEnds()
        round += 1

partOne()

elf_ap = 4
while not partTwo(elf_ap):
    elf_ap += 1
