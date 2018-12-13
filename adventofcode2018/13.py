with open('input13') as fp:
    track = [list(l.strip('\n')) for l in fp]
carts = []
for y, row in enumerate(track):
    for x, c in enumerate(row):
        if c in '<>^v':
            carts.append([x, y, c, 0])
            if c in '<>':
                row[x] = '-'
            else:
                row[x] = '|'

ans1, ans2 = None, None
removed = []
while len(removed) < len(carts) - 1:
    for i, cart in enumerate(carts):
        if i in removed:
            continue

        # move to next position
        c = cart[2]
        if c == '>':
            cart[0] += 1
        elif c == '<':
            cart[0] -= 1
        elif c == 'v':
            cart[1] += 1
        else: # c == '^'
            cart[1] -= 1

        # update the cart's direction
        t = track[cart[1]][cart[0]]
        if t == '/':
            if c == '>':
                c = '^'
            elif c == '<':
                c = 'v'
            elif c == 'v':
                c = '<'
            else: # c == '^'
                c = '>'
        elif t == '\\':
            if c == '>':
                c = 'v'
            elif c == '<':
                c = '^'
            elif c == 'v':
                c = '>'
            else: # c == '^'
                c = '<'
        elif t == '+':
            if cart[3] % 3 == 0: # turn left
                if c == '>':
                    c = '^'
                elif c == '<':
                    c = 'v'
                elif c == 'v':
                    c = '>'
                else: # c == '^'
                    c = '<'
            elif cart[3] % 3 == 2: # turn right
                if c == '>':
                    c = 'v'
                elif c == '<':
                    c = '^'
                elif c == 'v':
                    c = '<'
                else: # c == '^'
                    c = '>'
            cart[3] += 1
        cart[2] = c

        # remove crashed carts
        for j, cart2 in enumerate(carts):
            if j not in removed and j != i and cart[:2] == cart2[:2]:
                removed += [i, j]
                if not ans1:
                    ans1 = cart[:2]

for i, cart in enumerate(carts):
    if i not in removed:
        ans2 = cart[:2]

print(ans1)
print(ans2)