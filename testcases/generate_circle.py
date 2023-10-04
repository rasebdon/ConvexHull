import math

def exportCircle(pointCount, r=20000):
    a = 300
    b = 300

    #The lower this value the higher quality the circle is with more points generated
    stepSize = (2 * math.pi) / pointCount

    #Generated vertices
    positions = []

    t = 0
    while t < 2 * math.pi:
        positions.append((r * math.cos(t) + a, r * math.sin(t) + b))
        t += stepSize

    if len(positions) == (pointCount + 1):
        positions.pop()

    file = open(f"circle_{pointCount}.txt", "w")
    file.write(f"{len(positions)}\n")
    for pos in positions:
        file.write(f"{pos[0]},{pos[1]}\n")

    file.close()

for i in [1000, 10000, 100000, 250000, 500000, 1000000]:
    exportCircle(i)

exportCircle(10, 200)