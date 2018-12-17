def addr(reg, a, b, c):
    reg[c] = reg[a] + reg[b]

def addi(reg, a, b, c):
    reg[c] = reg[a] + b

def mulr(reg, a, b, c):
    reg[c] = reg[a] * reg[b]

def muli(reg, a, b, c):
    reg[c] = reg[a] * b

def banr(reg, a, b, c):
    reg[c] = reg[a] & reg[b]

def bani(reg, a, b, c):
    reg[c] = reg[a] & b

def borr(reg, a, b, c):
    reg[c] = reg[a] | reg[b]

def bori(reg, a, b, c):
    reg[c] = reg[a] | b

def setr(reg, a, b, c):
    reg[c] = reg[a]

def seti(reg, a, b, c):
    reg[c] = a

def gtir(reg, a, b, c):
    if a > reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

def gtri(reg, a, b, c):
    if reg[a] > b:
        reg[c] = 1
    else:
        reg[c] = 0

def gtrr(reg, a, b, c):
    if reg[a] > reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

def eqir(reg, a, b, c):
    if a == reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

def eqri(reg, a, b, c):
    if reg[a] == b:
        reg[c] = 1
    else:
        reg[c] = 0

def eqrr(reg, a, b, c):
    if reg[a] == reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

operations = [addr, addi, mulr, muli, banr, bani, borr, bori,
        setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr]

operation_candidates = [set(i for i in range(16)) for j in range(16)]

ans1 = 0

with open('input16') as fp:
    # part one
    while True:
        l1 = fp.readline()
        if 'Before' not in l1: # part one ends
            break
        l2 = fp.readline()
        l3 = fp.readline()
        fp.readline()
        before = [int(n) for n in l1[9:-2].split(', ')]
        instruction = [int(n) for n in l2.split(' ')]
        after = [int(n) for n in l3[9:-2].split(', ')]
        candidates = set()
        for idx, op in enumerate(operations):
            before2 = before[:]
            op(before2, instruction[1], instruction[2], instruction[3])
            if before2 == after:
                candidates.add(idx)
        operation_candidates[instruction[0]] &= candidates
        if len(candidates) >= 3:
            ans1 += 1

    # find opcodes's operation
    opcodes = [None] * 16
    for _ in range(16):
        for i, candidate in enumerate(operation_candidates):
            if candidate and len(candidate) == 1:
                idx = candidate.pop()
                opcodes[i] = operations[idx]
                for c in operation_candidates:
                    if idx in c:
                        c.remove(idx)
                break

    # part two
    reg = [0, 0, 0, 0]
    for l in fp:
        if l.strip():
            ins = [int(n) for n in l.split(' ')]
            op = opcodes[ins[0]]
            op(reg, ins[1], ins[2], ins[3])

print(ans1)
print(reg[0])
