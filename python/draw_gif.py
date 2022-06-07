import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib
import numpy as np

filename = '../data/02-15_17-26_'
filename_para = filename + 'para.csv'
filename_pos = filename + 'pos.csv'
filename_poly = filename + 'poly.csv'

matplotlib.use('agg')

para_list = []
with open(filename_para) as f_para:
    reader = csv.reader(f_para)
    for row in reader:
        row = list(map(float, row))
        para_list.append(row)

robot_num = int(para_list[0][0])
xlim = para_list[1][0:2]
ylim = para_list[1][2:4]

fig, ax = plt.subplots(figsize=(10, 10))
ax.set_aspect(1)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

t = np.linspace(0.0, 1.0, 1000)
c = np.sqrt(1 - np.square(t))
z = np.linspace(0.0, 0.0, 1000)
plt.fill_between(t, z, c, facecolor='green', alpha=.5)
plt.plot(t, c, 'k')

pos_x_list, pos_y_list, time_list, btry_list = [], [], [], []

with open(filename_pos) as f_pos:
    reader = csv.reader(f_pos)
    for row in reader:
        row = list(map(float, row))
        if len(row) == 1:
            time_list += row
        else:
            pos_x_list = pos_x_list + row[0::3]
            pos_y_list = pos_y_list + row[1::3]
            btry_list = btry_list + row[2::3]

assert (robot_num * len(time_list) == len(pos_x_list))
# assert(robot_num * len(time_list) != len(pos_x_list))

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

time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)

anno_list = []
for i in range(robot_num):
    anno_list.append(ax.annotate('E = %.1f' % (btry_list[i]),
                                 xy=(pos_x_list[i], pos_y_list[i])))


def update(num):
    pos_line.set_data(pos_x_list[num * robot_num: (num + 1) * robot_num],
                      pos_y_list[num * robot_num: (num + 1) * robot_num])
    pos_line.axes.axis(xlim + ylim)
    # plt.title("Time: {%.2f}", time_list[num])
    for i in range(robot_num):
        anno_list[i].set_text('E = %.1f' % (btry_list[num * robot_num + i]))
        anno_list[i].set_position((pos_x_list[num * robot_num + i], pos_y_list[num * robot_num + i]))
        poly_line_list[i].set_data(poly_x_list[num * robot_num + i], poly_y_list[num * robot_num + i])
        poly_line_list[i].axes.axis(xlim + ylim)
    time_text.set_text('Time = %.2fs' % (time_list[num]))

    return pos_line, poly_line_list, time_text


ani = animation.FuncAnimation(fig, update, len(time_list), interval=20, blit=False)

ani.save(filename + 'res.gif')
