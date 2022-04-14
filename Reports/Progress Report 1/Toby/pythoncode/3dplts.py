import numpy as np
import matplotlib.pyplot as plt

ax1 = plt.axes(projection='3d')

offset = float(input("OFFSET: "))

limpet1 = [0,0,0]
limpet2 = [0.5,0.25,0.25+offset]
limpet3 = [0.5,-0.25,0.25+offset]
#limpet4 = [1,0,0]

#limpets = [limpet1, limpet2, limpet3, limpet4]
limpets = [limpet1, limpet2, limpet3]

for i in range(0, len(limpets)):
    ax1.scatter(limpets[i][0], limpets[i][1], limpets[i][2])
    for j in range(0, len(limpets)):
        x = [limpets[i][0], limpets[j][0]]
        y = [limpets[i][1], limpets[j][1]]
        z = [limpets[i][2], limpets[j][2]]

        ax1.plot(x, y, z)

ax1.view_init(elev=25, azim=-100)

ax1.set_xlim([0,1])
ax1.set_ylim([-0.5,0.5])
ax1.set_zlim([-0.25,0.25])

plt.show()
