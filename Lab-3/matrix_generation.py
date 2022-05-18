import numpy as np
import random as rnd

eps = 1e-3


def has_zero_minors(matrix, k):
    for i in range(1, k + 1):
        if abs(np.linalg.det(matrix[:i, :i])) < eps:
            return True
    return False


def generate_upper_triangle_matrix(size):
    result = np.zeros([size, size])
    for i in range(size):
        for j in range(i, size):
            if i == j:
                while result[i][j] == 0:
                    result[i][j] = rnd.randint(-10, 10)
            elif rnd.random() < 0.3:
                result[i][j] = rnd.randint(-10, 10)
    return result


def generate_down_triangle_matrix(size):
    result = np.zeros([size, size])
    for i in range(size):
        for j in range(i + 1):
            if i == j:
                while result[i][j] == 0:
                    result[i][j] = rnd.randint(-10, 10)
            elif rnd.random() < 0.3:
                result[i][j] = rnd.randint(-10, 10)
    return result


def generate_triangle_reversible_matrix(size, upper):
    result = np.zeros([size, size])
    while np.linalg.det(result) <= eps:
        if upper:
            result = generate_upper_triangle_matrix(size)
        else:
            result = generate_down_triangle_matrix(size)
    return result


def generate_sparse_matrix(size):
    result = np.zeros([size, size])
    for i in range(size):
        for j in range(size):
            if i == j:
                while result[i][j] == 0:
                    result[i][j] = rnd.randint(-10, 10)
            elif rnd.random() < 0.3:
                result[i][j] = rnd.randint(-10, 10)
    return result


def generate_system(size, a):
    x = np.array([rnd.randint(-10, 10) for i in range(size)])
    b = np.array([0] * size)
    for i in range(size):
        for j in range(size):
            b[i] += a[i][j] * x[j]
    return a, b, x


def generate_sequence(size, k):
    generated = generate_sparse_matrix(size)
    for i in range(size):
        s = 0
        for j in range(size):
            s += abs(generated[i][j])
        if k != 0:
            generated[i][i] = s + 10 ** k
        else:
            generated[i][i] = s
    return generated


def generate_gilbert_matrix(size):
    matrix = np.ones([size, size])
    for i in range(size):
        for j in range(size):
            matrix[i][j] /= (i + j + 1)
    return matrix
