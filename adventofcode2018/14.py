input = 509671
input2 = [int(c) for c in str(input)]

recipes = [3, 7]
elf1, elf2 = 0, 1
while True:
    n = recipes[elf1] + recipes[elf2]
    if n < 10:
        recipes.append(n)
    else:
        recipes.append(1)
        if recipes[-len(input2):] == input2:
            print(len(recipes) - len(input2))
            break
        recipes.append(n - 10)
    if recipes[-len(input2):] == input2:
        print(len(recipes) - len(input2))
        break
    elf1 = (elf1 + recipes[elf1] + 1) % len(recipes)
    elf2 = (elf2 + recipes[elf2] + 1) % len(recipes)
    #if len(recipes) == input + 10:
    #    print(''.join([str(i) for i in recipes[input:input + 10]]))
