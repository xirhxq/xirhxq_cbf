import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

filename = '../data/01-02_00-36_'
filename_para = filename + 'para.csv'
filename_pos = filename + 'pos.csv'
filename_poly = filename + 'poly.csv'


para_list = []
with open(filename_para) as f_para:
    reader = csv.reader(f_para)
    for row in reader:
        row = list(map(float, row))
        para_list.append(row)

robot_num = int(para_list[0][0])
xlim = para_list[1][0:2]
ylim = para_list[1][2:4]

fig, ax = plt.subplots(figsize=(10,10))
ax.set_aspect(1)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

pos_x_list, pos_y_list = [], []

with open(filename_pos) as f_pos:
    reader = csv.reader(f_pos)
    for row in reader:
        row = list(map(float, row))
        pos_x_list = pos_x_list + row[0::2]
        pos_y_list = pos_y_list + row[1::2]

pos_line, = ax.plot(pos_x_list, pos_y_list, 'b*')

poly_x_list, poly_y_list = [], []
with open(filename_poly) as f_poly:
    reader = csv.reader(f_poly)
    for row in reader:
        row = list(map(float, row))
        poly_x_list.append(row[1::2])
        poly_y_list.append(row[2::2])

poly_line_list = []
for i in range(robot_num):
    tmp_poly_line, = ax.plot(poly_x_list[i], poly_y_list[i], 'k')
    poly_line_list.append(tmp_poly_line)


def update(num, x_list, y_list, line, plxlist, plylist, plyline):
    line.set_data(x_list[num * robot_num : (num + 1) * robot_num],
                  y_list[num * robot_num : (num + 1) * robot_num])
    line.axes.axis(xlim + ylim)
    for i in range(robot_num):
        plyline[i].set_data(plxlist[num * robot_num + i],
                            plylist[num * robot_num + i])
        plyline[i].axes.axis(xlim + ylim)
    return line, plyline

ani = animation.FuncAnimation(fig, update, int(len(pos_x_list) / robot_num),
                              fargs=[pos_x_list, pos_y_list, pos_line,
                                     poly_x_list, poly_y_list, poly_line_list],
                              interval=10, blit=False)

ani.save(filename + 'res.gif')