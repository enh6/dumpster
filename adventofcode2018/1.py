import sys

# load input numbers to a list
with open('input1') as fp:
    nums = [int(line) for line in fp]

# first puzzle
print(sum(nums))

# second puzzle
total = 0
freqs = set()

while True:
    for n in nums:
        total = total + n
        if total in freqs:
            print(total)
            sys.exit()
        freqs.add(total)
