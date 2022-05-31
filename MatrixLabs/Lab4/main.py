import Lab3.matrix_generation as mg
import Lab3.matrix as mt
import jakobi_rotation as jr
import numpy as np
import math as m
import matplotlib.pyplot as plt

n = [3, 5, 10, 15, 25, 30, 40, 50]
ks = range(1, 11)
eps = [1e-40]

for i in range(1, 20):
    eps.append(eps[i - 1] * 100)


def count_error(a, labd):
    res = 0
    for i in labd:
        p = a - i * np.diag(np.ones(a.shape[0]))
        res += np.linalg.det(p) ** 2
    return m.sqrt(res)


def gilbert_test_eps():
    f = open('output/gilbert1.txt', 'w')
    f.write("eps iterations error\n")
    size = 10
    iterations = []
    errors = []
    m = mg.generate_gilbert_matrix(size)
    for e in eps:
        csr = mt.csr_matrix(m)
        jr_solution = jr.solve(csr, e)
        print(jr_solution[0])
        iterations.append(jr_solution[1])
        err = count_error(m, jr_solution[0])
        errors.append(err)
        s = str(e) + " " + str(jr_solution[1]) + " " + str(err) + "\n"
        f.write(s)
        print(s)
    f.close()
    plt.scatter(range(-40, 0, 2), errors)
    plt.xlabel("Accuracy")
    plt.ylabel("Error")
    plt.title("size = " + str(size))
    plt.show()

    plt.scatter(range(-40, 0, 2), iterations)
    plt.xlabel("Accuracy")
    plt.ylabel("Iterations")
    plt.title("size = " + str(size))
    plt.show()


def gilbert_test_size():
    iterations = []
    errors = []
    f = open('output/gilbert2.txt', 'w')
    f.write("size iterations error\n")
    e = 1e-10
    iterations.clear()
    errors.clear()
    for size in n:
        m = mg.generate_gilbert_matrix(size)
        csr = mt.csr_matrix(m)
        jr_solution = jr.solve(csr, e)
        iterations.append(jr_solution[1])
        err = count_error(m, jr_solution[0])
        errors.append(err)
        s = str(size) + " " + str(jr_solution[1]) + " " + str(err) + "\n"
        f.write(s)
        print(s)

    f.close()
    plt.scatter(n, errors)
    plt.xlabel("Size")
    plt.ylabel("Error")
    plt.title("eps = " + str(e))
    plt.show()

    plt.scatter(n, iterations)
    plt.xlabel("Size")
    plt.ylabel("Iterations")
    plt.title("eps = " + str(e))
    plt.show()


def seq_test_eps():
    f = open('output/seq1.txt', 'w')
    f.write("eps iterations error\n")
    size = 20
    k = 5
    iterations = []
    errors = []
    m = mg.generate_sequence(size, k)
    for e in eps:
        csr = mt.csr_matrix(m)
        jr_solution = jr.solve(csr, e)
        print(jr_solution[0])
        iterations.append(jr_solution[1])
        err = count_error(m, jr_solution[0])
        errors.append(err)
        s = str(e) + " " + str(jr_solution[1]) + " " + str(err) + "\n"
        f.write(s)
        print(s)
    f.close()
    plt.scatter(range(-40, 0, 2), errors)
    plt.xlabel("Accuracy")
    plt.ylabel("Error")
    plt.title("size = " + str(size) + " k = " + str(k))
    plt.show()

    plt.scatter(range(-40, 0, 2), iterations)
    plt.xlabel("Accuracy")
    plt.ylabel("Iterations")
    plt.title("size = " + str(size) + " k = " + str(k))
    plt.show()


def seq_test_size():
    f = open('output/seq2.txt', 'w')
    f.write("size iterations error\n")
    e = 1e-15
    k = 5
    iterations = []
    errors = []
    iterations.clear()
    errors.clear()
    for size in n:
        m = mg.generate_sequence(size, k)
        csr = mt.csr_matrix(m)
        jr_solution = jr.solve(csr, e)
        iterations.append(jr_solution[1])
        err = count_error(m, jr_solution[0])
        errors.append(err)
        s = str(size) + " " + str(jr_solution[1]) + " " + str(err) + "\n"
        f.write(s)
        print(s)

    f.close()
    plt.scatter(n, errors)
    plt.xlabel("Size")
    plt.ylabel("Error")
    plt.title("eps = " + str(e) + " k = " + str(k))
    plt.show()

    plt.scatter(n, iterations)
    plt.xlabel("Size")
    plt.ylabel("Iterations")
    plt.title("eps = " + str(e) + " k = " + str(k))
    plt.show()


def seq_test_k():
    f = open('output/seq3.txt', 'w')
    f.write("k iterations error\n")
    e = 1e-15
    size = 20
    iterations = []
    errors = []
    iterations.clear()
    errors.clear()
    for k in ks:
        m = mg.generate_sequence(size, k)
        csr = mt.csr_matrix(m)
        jr_solution = jr.solve(csr, e)
        iterations.append(jr_solution[1])
        err = count_error(m, jr_solution[0])
        errors.append(err)
        s = str(k) + " " + str(jr_solution[1]) + " " + str(err) + "\n"
        f.write(s)
        print(s)

    f.close()
    plt.scatter(ks, errors)
    plt.xlabel("k")
    plt.ylabel("Error")
    plt.title("size = " + str(size) + " eps = " + str(e))
    plt.show()

    plt.scatter(ks, iterations)
    plt.xlabel("k")
    plt.ylabel("Iterations")
    plt.title("size = " + str(size) + " eps = " + str(e))
    plt.show()


# gilbert_test_eps()
gilbert_test_size()
# seq_test_k()
# seq_test_eps()
# seq_test_size()

