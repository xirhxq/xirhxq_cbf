import json
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
from matplotlib.patches import Wedge
import matplotlib
import os
import re
import math


ptn = re.compile('.*.json')
src = 'data'
files = os.listdir(src)

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

cir = []
for i in range(data_dict["para"]["charge"]["num"]):
    cir.append(Circle(xy=(data_dict["para"]["charge"]["pos"][i]["x"], data_dict["para"]["charge"]["pos"][i]["y"]),
                      radius=data_dict["para"]["charge"]["dist"][i], alpha=0.5))
    ax.add_patch(cir[i])

robot_num = data_dict["para"]["number"]

wed = []
for i in range(robot_num):
    c = data_dict["state"][0]["robot"][i]
    wed.append(Wedge(center=[c["x"], c["y"]], r=0.5, theta1=c["camera"] - 15, theta2=c["camera"] + 15))
    ax.add_patch(wed[i])

none_list = [0] * robot_num
pos_x_list, pos_y_list, batt_list = none_list, none_list, none_list
poly_x_list, poly_y_list = none_list, none_list

pos_line, = ax.plot(pos_x_list, pos_y_list, 'b*')
time_text = ax.text(0.05, 0.95, '', transform=ax.transAxes)

poly_line_list, anno_list = [], []
for i in range(robot_num):
    tmp_poly_line, = ax.plot(poly_x_list[i], poly_y_list[i], 'k')
    poly_line_list.append(tmp_poly_line)
    anno_list.append(ax.annotate('E = %.1f' % (batt_list[i]), xy=(pos_x_list[i], pos_y_list[i])))


def update(num):
    pos_x_list = [data_dict["state"][num]["robot"][i]["x"] for i in range(robot_num)]
    pos_y_list = [data_dict["state"][num]["robot"][i]["y"] for i in range(robot_num)]
    batt_list = [data_dict["state"][num]["robot"][i]["batt"] for i in range(robot_num)]

    if "cvt" in data_dict["state"][num]:
        poly_x_list = [[data_dict["state"][num]["cvt"][i]["pos"][j]["x"]
                        for j in range(data_dict["state"][num]["cvt"][i]["num"])] for i in range(robot_num)]
        poly_y_list = [[data_dict["state"][num]["cvt"][i]["pos"][j]["y"]
                        for j in range(data_dict["state"][num]["cvt"][i]["num"])] for i in range(robot_num)]

    pos_line.set_data(pos_x_list, pos_y_list)
    pos_line.axes.axis(data_dict["para"]["lim"]["x"] + data_dict["para"]["lim"]["y"])

    for i in range(robot_num):
        c = data_dict["state"][num]["robot"][i]
        wed[i].set_center([c["x"], c["y"]])
        wed[i].set_theta1(math.degrees(c["camera"]) - 15)
        wed[i].set_theta2(math.degrees(c["camera"]) + 15)
        anno_list[i].set_text('E = %.2f C = %.3f' % (batt_list[i], math.degrees(c["camera"])))
        if "cvt" in data_dict["state"][num]:
            anno_list[i].set_position((pos_x_list[i], pos_y_list[i]))
            poly_line_list[i].set_data(poly_x_list[i], poly_y_list[i])
            poly_line_list[i].axes.axis(data_dict["para"]["lim"]["x"] + data_dict["para"]["lim"]["y"])

    time_text.set_text('Time = %.2fs' % (data_dict["state"][num]["runtime"]))

    return pos_line, poly_line_list, time_text


ani = animation.FuncAnimation(fig, update, len(data_dict["state"]),
                              interval=int(1000 * (data_dict["state"][1]["runtime"]
                                           - data_dict["state"][0]["runtime"])),
                              blit=False)

ani.save(filename + 'res.gif')
