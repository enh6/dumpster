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

opcodes = {}
opcodes['addr'] = addr
opcodes['addi'] = addi
opcodes['mulr'] = mulr
opcodes['muli'] = muli
opcodes['banr'] = banr
opcodes['bani'] = bani
opcodes['borr'] = borr
opcodes['bori'] = bori
opcodes['setr'] = setr
opcodes['seti'] = seti
opcodes['gtir'] = gtir
opcodes['gtri'] = gtri
opcodes['gtrr'] = gtrr
opcodes['eqir'] = eqir
opcodes['eqri'] = eqri
opcodes['eqrr'] = eqrr

with open('input19') as fp:
    ip_reg = int(fp.readline()[4])
    code = []
    for l in fp:
        l = l.split(' ')
        code.append([opcodes[l[0]], int(l[1]), int(l[2]), int(l[3])])

ip = 0
reg = [0, 0, 0, 0, 0, 0]
while ip < len(code):
    reg[ip_reg] = ip
    ins = code[ip]
    opcode = ins[0]
    opcode(reg, ins[1], ins[2], ins[3])
    ip = reg[ip_reg] + 1
print(reg[0])

# part two
# guess the code's functionality from the instructions
# the code init register 5 and then execute loops from ip=1 to ip=16
# part one init r5 to 950, and part two init r5 to 10551350
# it loops r2 from 1 to r5, loops r4 from 1 to r5
# if r2 * r4 == r5, add r2 to r0
# so r0 is the sum of r5's divisors

r0 = 0
r5 = 10551350
for r2 in range(1, r5 + 1):
    if r5 % r2 == 0:
        r0 += r2
print(r0)

