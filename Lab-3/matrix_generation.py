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
            result[i][j] = rnd.randint(-10, 10)
    return result


def generate_down_triangle_matrix(size):
    result = np.zeros([size, size])
    for i in range(size):
        for j in range(i + 1):
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
    while has_zero_minors(result, size):
        result = np.zeros([size, size])
        for i in range(size):
            for j in range(size):
                if i == j:
                    result[i][j] = rnd.randint(-10, 10)
                elif rnd.random() < 0.3:
                    result[i][j] = rnd.randint(-10, 10)
    return result


def generate_system(size):
    a = generate_sparse_matrix(size)
    x = np.array([rnd.randint(-10, 10) for i in range(size)])
    b = np.array([0] * size)
    for i in range(size):
        for j in range(size):
            b[i] += a[i][j] * x[j]
    return a, b, x
