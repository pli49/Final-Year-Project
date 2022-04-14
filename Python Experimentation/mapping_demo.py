import numpy as np
import matplotlib.pyplot as plt

def draw_circle(radius, pos):
    theta = np.linspace(0, 2*np.pi, 100)

    return [radius * np.cos(theta)+pos[0], radius * np.sin(theta)+pos[1]]

def draw_sphere(radius, pos):
    u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
    x = np.cos(u) * np.sin(v) * radius + pos[0]
    y = np.sin(u) * np.sin(v) * radius + pos[1]
    z = np.cos(v) * radius + pos[2]

    return [x, y, z]

def dist_pos(pos1, pos2):
    return np.sqrt((pos1[0] - pos2[0])**2 + (pos1[1] - pos2[1])**2)

def angle_pos(pos1, pos2):
    return np.arctan2(pos2[1]-pos1[1], pos2[0]-pos1[0])

def circle_intersects(r1, pos1, r2, pos2):
    d = dist_pos(pos1, pos2)
    if d < (r1 + r2):
        theta1 = np.arccos((r1**2 + d**2 - r2**2) / (2*d*r1)) + angle_pos(pos1, pos2)
        theta2 = -np.arccos((r1**2 + d**2 - r2**2) / (2*d*r1)) + angle_pos(pos1, pos2)
        intersect1 = [pos1[0] + r1 * np.cos(theta1), pos1[1] + r1 * np.sin(theta1)]
        intersect2 = [pos1[0] + r1 * np.cos(theta2), pos1[1] + r1 * np.sin(theta2)]
        return [intersect1, intersect2]
    else:
        theta = angle_pos(pos1, pos2)
        intersect1 = [pos1[0] + (r1 + (dist_pos(pos1, pos2) - r1 - r2)/2) * np.cos(theta), pos1[1] + (r1 + (dist_pos(pos1, pos2) - r1 - r2)/2) * np.sin(theta)]
        return intersect1, intersect1

def most_likely_device_location(points):
    smallest_error_val = np.inf
    small_errs = 0
    for i in range(len(points)):
        for j in range(1, len(points)):
            for k in range(2, len(points)):
                if((i != j) and (j != k) and (i != k)):
                    avg_err = (dist_pos(points[i], points[j]) + dist_pos(points[i], points[k]) + dist_pos(points[j], points[k]))/3
                    print("Average Err: {}, P1: {}, P2: {}, P3: {}".format(avg_err, points[i], points[j], points[k]))
                    if(avg_err < smallest_error_val):
                        smallest_error_val = avg_err
                        small_errs = [i, j, k]

    x_pos = (points[small_errs[0]][0] + points[small_errs[1]][0] + points[small_errs[2]][0])/3
    y_pos = (points[small_errs[0]][1] + points[small_errs[1]][1] + points[small_errs[2]][1])/3

    return [x_pos, y_pos]

if __name__ == "__main__":

    NOISE_PERCENT = 10

    device1 = [0, 0]
    device2 = [2, .5]
    device3 = [1.5, 1]
    device4 = [1, -1]

    r1_4 = dist_pos(device1, device4)
    r1_4 += r1_4 * ((np.random.rand(1) - 0.5) * NOISE_PERCENT/100)
    r2_4 = dist_pos(device2, device4)
    r2_4 += r2_4 * ((np.random.rand(1) - 0.5) * NOISE_PERCENT/100)
    r3_4 = dist_pos(device3, device4)
    r3_4 += r3_4 * ((np.random.rand(1) - 0.5) * NOISE_PERCENT/100)

    circ1_draw = draw_circle(r1_4, device1)
    circ2_draw = draw_circle(r2_4, device2)
    circ3_draw = draw_circle(r3_4, device3)

    int1, int2 = circle_intersects(r1_4, device1, r2_4, device2)
    int3, int4 = circle_intersects(r1_4, device1, r3_4, device3)
    int5, int6 = circle_intersects(r2_4, device2, r3_4, device3)


    device_loc = most_likely_device_location([int1, int2, int3, int4, int5, int6])

    plt.figure(1, figsize=(16,8))
    plt.subplot(121)

    plt.xlim(-5, 5)
    plt.ylim(-5, 5)
    plt.plot(circ1_draw[0], circ1_draw[1])
    plt.plot(circ2_draw[0], circ2_draw[1])
    plt.plot(circ3_draw[0], circ3_draw[1])
    plt.plot(int1[0], int1[1], 'ro')
    plt.plot(int2[0], int2[1], 'ro')
    plt.plot(int3[0], int3[1], 'ro')
    plt.plot(int4[0], int4[1], 'ro')
    plt.plot(int5[0], int5[1], 'ro')
    plt.plot(int6[0], int6[1], 'ro')

    plt.plot(device1[0], device1[1], 'bo')
    plt.text(device1[0], device1[1], "1")
    plt.plot(device2[0], device2[1], 'bo')
    plt.text(device2[0], device2[1], "2")
    plt.plot(device3[0], device3[1], 'bo')
    plt.text(device3[0], device3[1], "3")
    plt.plot(device4[0], device4[1], 'bo')
    plt.text(device4[0], device4[1], "4")

    plt.subplot(122)
    plt.xlim(-5, 5)
    plt.ylim(-5, 5)
    plt.plot(circ1_draw[0], circ1_draw[1])
    plt.plot(circ2_draw[0], circ2_draw[1])
    plt.plot(circ3_draw[0], circ3_draw[1])
    plt.plot(int1[0], int1[1], 'ro')
    plt.plot(int2[0], int2[1], 'ro')
    plt.plot(int3[0], int3[1], 'ro')
    plt.plot(int4[0], int4[1], 'ro')
    plt.plot(int5[0], int5[1], 'ro')
    plt.plot(int6[0], int6[1], 'ro')

    plt.plot(device_loc[0], device_loc[1], 'go')

    #----------------------------------------------------------------------
    # 3D Attempt

    sphere1 = draw_sphere(1, [0,0,0])



    fig2 = plt.figure(2)
    ax2 = plt.axes(projection='3d')

    ax2.plot_surface(sphere1[0], sphere1[1], sphere1[2], alpha=0.3)


    plt.show()