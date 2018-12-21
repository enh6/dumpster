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

with open('input21') as fp:
    ip_reg = int(fp.readline()[4])
    code = []
    for l in fp:
        l = l.split(' ')
        code.append([opcodes[l[0]], int(l[1]), int(l[2]), int(l[3])])

# part one
# program halts only when executing instruction 28 and r0 == r1
ip = 0
reg = [0, 0, 0, 0, 0, 0]
while ip < len(code):
    reg[ip_reg] = ip
    ins = code[ip]
    opcode = ins[0]
    opcode(reg, ins[1], ins[2], ins[3])
    ip = reg[ip_reg] + 1
    if ip == 28:
        print(reg[1])
        break

# part two
# reconstruct the program's logic from instructions
# program generates r1 in a loop
numbers = set()
r1 = 0
while True:
    r3 = r1 | 0x10000
    r1 = 6780005
    while r3:
        r1 = r1 + (r3 & 0xff)
        r1 = r1 & 0xffffff
        r1 = r1 * 65899
        r1 = r1 & 0xffffff
        r3 = r3 >> 8
    if r1 in numbers:
        print(prev)
        break
    else:
        numbers.add(r1)
        prev = r1
