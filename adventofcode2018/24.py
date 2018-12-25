from re import match
from copy import deepcopy
groups = []
with open('input24') as fp:
    for army in ['immune', 'infect']:
        fp.readline()
        while True:
            l = fp.readline().strip()
            if not l:
                break
            matches = match('(\d+) units each with (\d+) hit points(?: \((.*)\))? with an attack that does (\d+) (\w*) damage at initiative (\d+)', l).groups()
            group = {'army': army}
            group['unit'] = int(matches[0])
            group['hp'] = int(matches[1])
            if matches[2]:
                m = matches[2].split('; ')
                for t in m:
                    if 'immune' in t:
                        group['immune'] = t.replace('immune to ', '').split(', ')
                    if 'weak' in t:
                        group['weak'] = t.replace('weak to ', '').split(', ')
            group['damage'] = int(matches[3])
            group['damage_type'] = matches[4]
            group['initiative'] = int(matches[5])
            groups.append(group)

def calculateDamage(attacker, target):
    damage_type = attacker['damage_type']
    if 'immune' in target and damage_type in target['immune']:
        return 0
    damage = attacker['unit'] * attacker['damage']
    if 'weak' in target and damage_type in target['weak']:
        damage *= 2
    return damage

def combat(groups):
    while True:
        # sort groups by target selection order
        groups.sort(key = lambda g : (g['unit'] * g['damage'], g['initiative']), reverse = True)

        # target select
        attacks = []
        targets = []
        for group in groups:
            if group['unit'] <= 0:
                continue
            target = None
            target_idx = 0
            max_damage = 0
            for idx, t in enumerate(groups):
                if t['unit'] <= 0 or t['army'] == group['army'] or idx in targets:
                    continue
                damage = calculateDamage(group, t)
                if damage == 0:
                    continue
                if damage > max_damage:
                    max_damage = damage
                    target = t
                    target_idx = idx
                elif damage == max_damage:
                    if t['unit'] * t['damage'] > target['unit'] * target['damage']:
                        max_damage = damage
                        target = t
                        target_idx = idx
                    elif t['unit'] * t['damage'] == target['unit'] * target['damage']:
                        if t['initiative'] > target['initiative']:
                            max_damage == damage
                            target = t
                            target_idx = idx
            if target:
                targets.append(target_idx)
                attacks.append((group, target))

        # no target, end combat
        if not targets:
            break

        # attack in decreasing order of initiative
        attacks.sort(key = lambda attack: attack[0]['initiative'], reverse = True)
        for attacker, target in attacks:
            if attacker['unit'] > 0:
                damage = calculateDamage(attacker, target)
                kill = damage // target['hp']
                target['unit'] -= kill

ans1 = 0
groups1 = deepcopy(groups)
combat(groups1)
for g in groups1:
    if g['unit'] > 0:
        ans1 += g['unit']
print(ans1)

# part two
boost = 1
immune_win = False
while not immune_win:
    groups2 = deepcopy(groups)
    for g in groups2:
        if g['army'] == 'immune':
            g['damage'] += boost
    combat(groups2)
    immune_win = True
    ans2 = 0
    for g in groups2:
        if g['unit'] > 0:
            if g['army'] == 'infect':
                immune_win = False
                continue
            else:
                ans2 += g['unit']
    boost += 1
print(ans2)
