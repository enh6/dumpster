with open('input8') as fp:
    nums = [int(n) for n in fp.read().split()]

idx = 0
def process():
    global idx
    sum = 0
    child_num, meta_num = nums[idx], nums[idx + 1]
    idx += 2
    for i in range(child_num):
        sum += process()
    for i in range(meta_num):
        sum += nums[idx]
        idx += 1
    return sum
print(process())

idx = 0
def process2():
    global idx
    value = 0
    child_num, meta_num = nums[idx], nums[idx + 1]
    idx += 2
    if child_num == 0:
        for i in range(meta_num):
            value += nums[idx]
            idx += 1
        return value
    else:
        child_values = []
        for i in range(child_num):
            child_values.append(process2())
        for i in range(meta_num):
            if nums[idx] and nums[idx] <= child_num:
                value += child_values[nums[idx] - 1]
            idx += 1
        return value
print(process2())
