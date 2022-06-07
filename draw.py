import json
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib
import numpy as np

filename = 'data/02-21_17-41_data.json'
filename = filename[:-9]

with open(filename + 'data.json') as f:
    data_dict = json.load(f)

matplotlib.use('agg')

fig, ax = plt.subplots(figsize=(10, 10))
ax.set_aspect(1)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

t = np.linspace(0.0, 1.0, 1000)
c = np.sqrt(1 - np.square(t))
z = np.linspace(0.0, 0.0, 1000)
plt.fill_between(t, z, c, facecolor='green', alpha=.5)
plt.plot(t, c, 'k')

robot_num = data_dict["para"]["number"]

none_list = [0] * robot_num
pos_x_list, pos_y_list, batt_list = none_list, none_list, none_list
poly_x_list, poly_y_list = none_list, none_list

pos_line, = ax.plot(pos_x_list, pos_y_list, 'b*')
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)

poly_line_list, anno_list = [], []
for i in range(robot_num):
    tmp_poly_line, = ax.plot(poly_x_list[i], poly_y_list[i], 'k')
    poly_line_list.append(tmp_poly_line)
    anno_list.append(ax.annotate('E = %.1f' % (batt_list[i]), xy=(pos_x_list[i], pos_y_list[i])))


def update(num):
    pos_x_list = [data_dict["state"][num]["robot"][i]["x"] for i in range(robot_num)]
    pos_y_list = [data_dict["state"][num]["robot"][i]["y"] for i in range(robot_num)]
    btry_list = [data_dict["state"][num]["robot"][i]["btry"] for i in range(robot_num)]

    poly_x_list = [[data_dict["state"][num]["cvt"][i]["pos"][j]["x"]
                    for j in range(data_dict["state"][num]["cvt"][i]["num"])] for i in range(robot_num)]
    poly_y_list = [[data_dict["state"][num]["cvt"][i]["pos"][j]["y"]
                    for j in range(data_dict["state"][num]["cvt"][i]["num"])] for i in range(robot_num)]

    pos_line.set_data(pos_x_list, pos_y_list)
    pos_line.axes.axis(data_dict["para"]["lim"]["x"] + data_dict["para"]["lim"]["y"])

    for i in range(robot_num):
        anno_list[i].set_text('E = %.1f' % (btry_list[i]))
        anno_list[i].set_position((pos_x_list[i], pos_y_list[i]))
        poly_line_list[i].set_data(poly_x_list[i], poly_y_list[i])
        poly_line_list[i].axes.axis(data_dict["para"]["lim"]["x"] + data_dict["para"]["lim"]["y"])

    time_text.set_text('Time = %.2fs' % (data_dict["state"][num]["runtime"]))

    return pos_line, poly_line_list, time_text


ani = animation.FuncAnimation(fig, update, len(data_dict["state"]), interval=20, blit=False)

ani.save(filename + 'res.gif')
