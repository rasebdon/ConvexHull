import math

a = 300
b = 300
r = 200

#The lower this value the higher quality the circle is with more points generated
stepSize = 0.5

#Generated vertices
positions = []

t = 0
while t < 2 * math.pi:
    positions.append((r * math.cos(t) + a, r * math.sin(t) + b))
    t += stepSize

file = open("worst_case_quickhull.txt", "w")
file.write(f"{len(positions)}\n")
for pos in positions:
    file.write(f"{pos[0]} {pos[1]}\n")

file.close()