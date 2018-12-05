import re

logs = []
with open('input4') as fp:
    logs = [l for l in fp]
logs.sort()

guards = {}
for log in logs:
    num = int(re.findall('\d+', log)[-1])
    if 'Guard' in log:
        ID = num
        if ID in guards:
            record = guards[ID]
        else:
            record = [0] * 60
            guards[ID] = record
    elif 'falls asleep' in log:
        begin_sleep = num
    else: # wakes up
        wake_up = num
        for i in range(begin_sleep, wake_up):
            record[i] += 1

max_time = 0
max_freq = 0

for ID, record in guards.items():
    t_sum = sum(record)
    t_max = max(record)
    if t_sum > max_time:
        max_time = t_sum
        ID1 = ID
        minute1 = record.index(t_max)
    if t_max > max_freq:
        max_freq = t_max
        ID2 = ID
        minute2 = record.index(t_max)

print(ID1 * minute1)
print(ID2 * minute2)
