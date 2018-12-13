# get 1) initial state 2) notes that can generate
with open('input12') as fp:
    state = fp.readline().strip().split(': ')[1]
    fp.readline()
    notes = [l.strip().split(' => ') for l in fp]
notes = [n[0] for n in notes if n[1] == '#']

start = 0
ans = 0
for i in range(200):
    # pad state with '...'
    while '#' in state[:3]:
        start -= 1
        state = '.' + state
    while '#' in state[-3:]:
        state = state + '.'

    next_state = ''
    start += 2
    for j in range(len(state) - 4):
        if state[j:j + 5] in notes:
            next_state += '#'
        else:
            next_state += '.'
    state = next_state
    prev = ans
    ans = sum([(start + i) for i, c in enumerate(state) if c == '#'])
    # we can see the sum increases at constant speed after some generatioins
    print(ans - prev)
    if (i == 19):
        ans1 = ans
ans2 = ans + (ans - prev) * (50000000000 - 200)
print(ans1, ans2)




