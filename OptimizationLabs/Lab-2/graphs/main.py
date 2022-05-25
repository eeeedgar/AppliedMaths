import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from textwrap import wrap


def f1(x, y):
    return x ** 2 + y ** 2


def f2(x, y):
    return 10 * x ** 2 + y ** 2


def f3(x, y):
    return x ** 2 + x * y - 6 * y ** 2


def func(i):
    if i == 1:
        return f1
    if i == 2:
        return f2
    if i == 3:
        return f3
    return f_1


def func_str(i):
    if i == 1:
        return "x^2 + y^2"
    if i == 2:
        return "10x^2 + y^2"
    if i == 3:
        return "x^2 + xy - 6y^2"
    return "unknown"


def get_route(str, x, y, st):
    strings = str.split("\n")
    for s in strings[0:-2]:
        iter, x_prev, y_prev, x_curr, y_curr, step = [float(i) for i in s.split("\t")]
        x.append(x_curr)
        y.append(y_curr)
        st.append(step)
    return [x, y, st]


def make_graph(directory_name):
    files = os.listdir(directory_name)
    txt_files = filter(lambda x: x[-4:] == '.txt', files)
    for file_name in txt_files:
        stream = open(directory_name + "/" + file_name, "r")
        stream.readline()
        step = stream.readline()
        start_x, start_y = [float(i) for i in stream.readline().split(";")]
        s = []
        x = [start_x]
        y = [start_y]
        stream.readline()
        str = stream.read()
        route = get_route(str, x, y, s)
        ans = str.split("\n")[-2]
        i = int(file_name.split(")")[0].split("function")[1])
        make_data(i, step, route, route[2][0], ans)


def make_data(fun_num, title, route, step, ans):
    x_max = max([abs(i) for i in route[0]])
    y_max = max([abs(i) for i in route[1]])
    f = max(x_max, y_max) + 1
    x = np.arange(-abs(f), abs(f), f / 100)
    y = np.arange(-abs(f), abs(f), f / 100)
    xgrid, ygrid = np.meshgrid(x, y)
    z = func(fun_num)(xgrid, ygrid)

    if title != "Fractional step" or title != "Conjugate gradients":
        title += ", (step = " + str(step) + ")"
    title += ", z = " + func_str(fun_num)
    title += ", iterations: " + str(len(route[0]))
    title += "\n" + ans
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("\n".join(wrap(title)), loc='center', wrap=True)
    cs = plt.contour(xgrid, ygrid, z)
    plt.clabel(cs)
    plt.scatter(route[0], route[1], edgecolors='r')
    plt.plot(route[0], route[1])
    plt.show()
    return xgrid, ygrid, z


# make_graph("../outputs/constant_step")
# make_graph("../outputs/fractional_step")
# make_graph("../outputs/golden_ratio_step")
# make_graph("../outputs/fibonacci_step")
# make_graph("../outputs/conjugate_gradients")
make_graph("../outputs/linear")

# for i in range(1, 4):
#     fig = plt.figure()
#     ax = fig.gca(projection='3d')
#     x = np.arange(-10, 10, 0.1)
#     y = np.arange(-10, 10, 0.1)
#     x, y = np.meshgrid(x, y)
#     z = func(i)(x, y)
#     surf = ax.plot_surface(x, y, z, cmap=cm.coolwarm,
#                            linewidth=0, antialiased=False)
#     fig.colorbar(surf, shrink=0.5, aspect=5)
#     plt.show()
