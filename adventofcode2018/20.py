with open('input20') as fp:
    input = list(fp.readline().strip('^$\n'))

(x, y) = (0, 0)
dist = 0
rooms = {}
stack = [(0, 0)]
rooms[(x, y)] = dist
ans1, ans2 = 0, 0
for c in input:
    if c == '(':
        stack.append((x, y))
    elif c == ')':
        (x, y) = stack.pop()
        dist = rooms[(x, y)]
    elif c == '|':
        (x, y) = stack[-1]
        dist = rooms[(x, y)]
    else: # NSEW
        if c == 'N':
            y -= 1
        elif c == 'S':
            y += 1
        elif c == 'W':
            x -= 1
        else: # c == 'E':
            x += 1

        dist += 1
        if (x, y) not in rooms:
            rooms[(x, y)] = dist
            if dist > ans1:
                ans1 = dist
            if dist >= 1000:
                ans2 += 1
print(ans1, ans2)
