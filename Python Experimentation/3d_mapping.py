import numpy as np
from scipy.optimize import fsolve
import matplotlib.pyplot as plt
import imageio
import os
import time

class device:

    # contains a list of lists, [device, distance]
    connections = []
    pos = [0, 0, 0]
    pos_found = False
    radius = 0
    distance_measurements = []
    
    def system_of_equations(self, p):
        x, y, z = p
        
        out1 = np.sqrt((x-self.connections[0][0].pos[0])**2+(y-self.connections[0][0].pos[1])**2+(z-self.connections[0][0].pos[2])**2) - self.connections[0][1]
        out2 = np.sqrt((x-self.connections[1][0].pos[0])**2+(y-self.connections[1][0].pos[1])**2+(z-self.connections[1][0].pos[2])**2) - self.connections[1][1]
        out3 = np.sqrt((x-self.connections[2][0].pos[0])**2+(y-self.connections[2][0].pos[1])**2+(z-self.connections[2][0].pos[2])**2) - self.connections[2][1]
        out3 = np.sqrt((x-self.connections[3][0].pos[0])**2+(y-self.connections[3][0].pos[1])**2+(z-self.connections[3][0].pos[2])**2) - self.connections[3][1]

        return out1, out2, out3

    def find_intersect(self):
        self.pos = fsolve(self.system_of_equations, (1, 1, 1))
    
    def plot_pos(self, fig, ax, point_color="r"):
        ax.scatter3D(self.pos[0], self.pos[1], self.pos[2], s=100, color=point_color)

    def plot_wire_sphere(self, fig, ax):
        u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
        x = self.radius * np.cos(u)*np.sin(v) + self.pos[0]
        y = self.radius * np.sin(u)*np.sin(v) + self.pos[1]
        z = self.radius * np.cos(v) + self.pos[2]
        ax.plot_wireframe(x, y, z, color="b", alpha=0.3)
            
    
        


if __name__ == "__main__":
    dev1 = device()
    dev1.pos = [2, 0, 0]
    dev1.radius = 2
    
    dev2 = device()
    dev2.pos = [-1, 0, 1]
    dev2.radius = 1.5

    dev3 = device()
    dev3.pos = [0, 1, 1]
    dev3.radius = 1

    dev4 = device()
    dev4.pos = [0, -1, 1]
    dev4.radius = 1

    dev5 = device()
    dev5.connections.append([dev1, 1])
    dev5.connections.append([dev2, 1])
    dev5.connections.append([dev3, 1])
    dev5.connections.append([dev4, 1])

    dev5.find_intersect()

    fig = plt.figure(1)
    ax = plt.axes(projection="3d")

    #dev1.plot_pos(fig, ax)
    dev1.plot_wire_sphere(fig, ax)
    dev1.plot_pos(fig, ax, 'g')
    #dev2.plot_pos(fig, ax)
    dev2.plot_wire_sphere(fig, ax)
    dev2.plot_pos(fig, ax, 'g')
    #dev3.plot_pos(fig, ax)
    dev3.plot_wire_sphere(fig, ax)
    dev3.plot_pos(fig, ax, 'g')
    #dev4.plot_pos(fig, ax)
    dev4.plot_wire_sphere(fig, ax)
    dev4.plot_pos(fig, ax, 'g')
    dev5.plot_pos(fig, ax)

    max_range = np.array([6,6,6]).max() / 2.0

    ax.set_xlim(-3,3)
    ax.set_ylim(-3,3)
    ax.set_zlim(-3,3)
    ax.set_box_aspect([1,1,1])

    filenames = []
    for i in range(1, 90, 1):
        ax.view_init(elev=30, azim=i)
        # plt.show()
        filename = f'{i}.png'
        filenames.append(filename)

        plt.draw()
        plt.savefig(filename)
        # plt.close()

    # build gif
    with imageio.get_writer('mygif.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)
            
    # Remove files
    for filename in set(filenames):
        os.remove(filename)
        
    

    