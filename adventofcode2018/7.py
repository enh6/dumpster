import copy

# get dependencies from input
atoz = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
deps = {c: [] for c in atoz}
with open('input7') as fp:
    for l in fp:
        deps[l[36]].append(l[5])

# part one
deps2 = copy.deepcopy(deps)
steps = ''
while deps2:
    step = min([s for s, dep in deps2.items() if not dep])
    steps += step
    deps2.pop(step)
    for dep in deps2.values():
        if step in dep:
            dep.remove(step)
print(steps)

# part two
t = 0
times = {c: 61 + i for i, c in enumerate(atoz)}
while deps:
    steps = [s for s, dep in deps.items() if not dep][:5]
    loop = True
    while loop:
        t += 1
        for step in steps:
            times[step] -= 1
            if times[step] == 0:
                loop = False
                deps.pop(step)
                for dep in deps.values():
                    if step in dep:
                        dep.remove(step)
print(t)
