from collections import deque

def max_score(player_num, marble_num):
    circle = deque([0])
    scores = [0] * player_num
    for i in range(marble_num):
        marble = i + 1
        if marble % 23:
            circle.rotate(2)
            circle.append(marble)
        else:
            player = i % player_num
            circle.rotate(-7)
            scores[player] += marble + circle.pop()
    return max(scores)

print(max_score(430, 71588))
print(max_score(430, 7158800))
