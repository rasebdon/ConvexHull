import math

def exportLine(pointCount):
    #Generated vertices
    positions = []

    for i in range(0, pointCount):
        positions.append((i, 0))

    file = open(f"line_{pointCount}.txt", "w")
    file.write(f"{len(positions)}\n")
    for pos in positions:
        file.write(f"{pos[0]},{pos[1]}\n")

    file.close()

for i in [10, 1000, 10000, 100000, 250000, 500000, 1000000, 10000000]:
    exportLine(i)