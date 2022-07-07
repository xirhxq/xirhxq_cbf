import json
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
from matplotlib.patches import Wedge
import matplotlib
import os
import re
import math
import numpy as np
import time

tic = time.time()
ptn = re.compile('.*.json')
src = 'data'
files = os.listdir(src)

# matplotlib.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
# matplotlib.rc('text', usetex=True)

json_files = []
for file in files:
    if re.match(ptn, file):
        json_files.append(f'{src}/{file}')

json_files.sort(key=lambda fp: os.path.getctime(fp), reverse=True)
newest_json = json_files[0]
print('find {}'.format(newest_json))

filename = newest_json
filename = filename[:-9]

with open(filename + 'data.json') as f:
    data_dict = json.load(f)

matplotlib.use('agg')

fig, ax = plt.subplots(figsize=(20, 10))
ax.set_aspect(1)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

interval = data_dict["state"][1]["runtime"] - data_dict["state"][0]["runtime"]
total_length = len(data_dict["state"])

robot_num = data_dict["para"]["number"]
world_x_list = [data["x"] for data in data_dict["para"]["world"]]
world_y_list = [data["y"] for data in data_dict["para"]["world"]]

x = np.linspace(0, 20, 200)
y = np.linspace(0, 10, 100)
X, Y = np.meshgrid(x, y)


def loop(x_min, x_max, y_min, y_max, t, v):
    dxt = (x_max - x_min) / v
    dyt = (y_max - y_min) / v
    dt = 2 * dxt + 2 * dyt
    while t >= dt:
        t -= dt
    if t < dxt:
        return x_min + v * t, y_min
    elif t < dxt + dyt:
        return x_max, y_min + (t - dxt) * v
    elif t < 2 * dxt + dyt:
        return x_max - (t - dxt - dyt) * v, y_max
    else:
        return x_min, y_max - (t - 2 * dxt - dyt) * v


def update(num):
    progress_percentage = num / total_length * 100
    elap_time = time.time() - tic
    if num > 0:
        eta = (100 - progress_percentage) / progress_percentage * elap_time
    else:
        eta = np.nan
    print("\r[%s%%]|%s elap: %.2fs eta: %.2fs" % (math.ceil(progress_percentage), "#" * (math.ceil(progress_percentage) // 2),
                                     elap_time, eta), end="")
    ax.clear()

    center_x, center_y = data_dict["state"][num]["target"]["x"], data_dict["state"][num]["target"]["y"]
    L = np.sqrt((X - center_x) ** 2 + (Y - center_y) ** 2)
    Z = np.exp(-np.fabs(L - data_dict["para"]["dens"]["r"]) * data_dict["para"]["dens"]["k"])
    ax.contourf(X, Y, Z, alpha=0.2)

    ax.add_patch(Circle(xy=(center_x, center_y), radius=0.2, color='r', alpha=0.2))
    ax.annotate('Target', xy=(center_x, center_y))

    for i in range(data_dict["para"]["charge"]["num"]):
        ax.add_patch(Circle(xy=(data_dict["para"]["charge"]["pos"][i]["x"], data_dict["para"]["charge"]["pos"][i]["y"]),
                            radius=data_dict["para"]["charge"]["dist"][i], alpha=0.5))

    pos_x_list = [data_dict["state"][num]["robot"][i]["x"] for i in range(robot_num)]
    pos_y_list = [data_dict["state"][num]["robot"][i]["y"] for i in range(robot_num)]
    batt_list = [data_dict["state"][num]["robot"][i]["batt"] for i in range(robot_num)]
    camera_list = [math.degrees(data_dict["state"][num]["robot"][i]["camera"]) for i in range(robot_num)]

    if "cvt" in data_dict["state"][num]:
        poly_x_list = [[data_dict["state"][num]["cvt"][i]["pos"][j]["x"]
                        for j in range(data_dict["state"][num]["cvt"][i]["num"])] for i in range(robot_num)]
        poly_y_list = [[data_dict["state"][num]["cvt"][i]["pos"][j]["y"]
                        for j in range(data_dict["state"][num]["cvt"][i]["num"])] for i in range(robot_num)]

    ax.plot(pos_x_list, pos_y_list, 'b*')

    for i in range(robot_num):
        ax.add_patch(Wedge(center=[pos_x_list[i], pos_y_list[i]], r=0.5, alpha=0.3,
                           theta1=camera_list[i] - 15, theta2=camera_list[i] + 15))

        ax.annotate(('    Robot #{}:' + '\n'
                    + r'$\quadE = {:.2f}$' + '\n'
                    + r'$\quad\theta = {:.2f}$').format(i + 1, batt_list[i], camera_list[i]),
                    xy=(pos_x_list[i], pos_y_list[i]))

        if "cvt" in data_dict["state"][num]:
            ax.plot(poly_x_list[i], poly_y_list[i], 'k')

    ax.text(0.05, 0.95, 'Time = {:.2f}s'.format(data_dict["state"][num]["runtime"]), transform=ax.transAxes)
    ax.set_xlim(data_dict["para"]["lim"]["x"])
    ax.set_ylim(data_dict["para"]["lim"]["y"])

    ax.plot(world_x_list, world_y_list, 'k')

    return


ani = animation.FuncAnimation(fig, update, len(data_dict["state"]),
                              interval=int(1000 * interval),
                              blit=False)

# ani.save(filename + 'res.gif')
# print("\ngif saved in {}".format(filename + 'res.gif'))

ani.save(filename + 'res.mp4', writer='ffmpeg', fps=int(1/interval))
print("\nmp4 saved in {}".format(filename + 'res.mp4'))

toc = time.time()
print("{:.2f} seconds elapsed".format(toc - tic))
