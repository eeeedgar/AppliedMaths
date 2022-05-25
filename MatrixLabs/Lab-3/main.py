import numpy as np
import matrix_generation as mg
import sle
import time
import math
import matplotlib.pyplot as plt

eps = [1e-3, 1e-6, 1e-9]
n1 = [10, 50, 10 ** 2]
n = [10, 50, 10 ** 2, 10 ** 3]
ks = [1, 3, 4, 6]


def distance(x, y):
    ans = 0
    for i in range(len(x)):
        ans += (x[i] - y[i]) ** 2
    return math.sqrt(ans)


def test_gauss_solution():
    f = open('../output/gauss_diag.txt', 'w')
    for size in n1:
        for k in ks:
            a = mg.generate_sequence(size, k)
            x = np.array([(i + 1) for i in range(size)])
            b = np.matmul(a, np.array(x))
            system = sle.sle(a, np.array([b]))
            start = time.time()
            ans = np.array(system.solve_gauss())
            end = time.time()
            s = str(size) + " " + str(k) + " " + str(distance(x, ans[0])) + " " + str(end - start) + "\n"
            print(s)
            f.write(s)
    f.close()
    f = open('../output/gauss_gilbert.txt', 'w')
    for size in n1:
        a = mg.generate_gilbert_matrix(size)
        x = np.array([(i + 1) for i in range(size)])
        b = np.matmul(a, np.array(x))
        system = sle.sle(a, np.array([b]))
        start = time.time()
        ans = system.solve_gauss()
        end = time.time()
        s = str(size) + " " + str(distance(x, ans[0])) + " " + str(end - start) + "\n"
        print(s)
        f.write(s)
    f.close()


def test_jacobi_solution():
    # f = open('output/jacbob_diag.txt', 'w')
    # f.write("size k iterations convergence error(b_norm) distance time\n")
    # for e in eps:
    #     for size in n:
    #         for k in ks:
    #             a = mg.generate_sequence(size, k)
    #             x = np.array([(i + 1) for i in range(size)])
    #             b = np.matmul(a, np.array(x))
    #             system = sle.sle(a, np.array([b]))
    #             start = time.time()
    #             ans = system.solve_jacobi(e)
    #             end = time.time()
    #             s = str(size) + " " + str(k) + " " + str(ans.iterations) + " " + str(ans.convergence) + " " + str(ans.error()) + " " + str(distance(ans.x, x)) + " " + str(end - start) + "\n"
    #             f.write(s)
    #             print(s)
    # f.close()
    f = open('../output/jackob_gilbert.txt', 'w')
    f.write("size iterations convergence b_norm distance time\n")
    for e in eps:
        for size in n:
            a = mg.generate_gilbert_matrix(size)
            x = np.array([(i + 1) for i in range(size)])
            b = np.matmul(a, np.array(x))
            system = sle.sle(a, np.array([b]))
            start = time.time()
            ans = system.solve_jacobi(e)
            end = time.time()
            s = str(size) + " " + str(ans.iterations) + " " + str(ans.convergence) + " " + str(
                ans.b_norm) + " " + str(distance(ans.x, x)) + " " + str(end - start) + "\n"
            f.write(s)
            print(s)
    f.close()


def make_graphs():
    eps = np.arange(1e-15, 1e-6, 1e-8)
    iterations = []
    size = 10
    for e in eps:
        k = 1
        a = mg.generate_sequence(size, k)
        x = np.array([(i + 1) for i in range(size)])
        b = np.matmul(a, np.array(x))
        system = sle.sle(a, np.array([b]))
        ans = system.solve_jacobi(e)
        iterations.append(ans.iterations)

    plt.plot(eps, iterations)
    plt.xlabel("Accuracy")
    plt.ylabel("Iterations")
    plt.title("size = 10, k = 1")
    plt.show()




# test_gauss_solution()
# test_jacobi_solution()

make_graphs()
