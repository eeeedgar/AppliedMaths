import numpy as np


def LU_decomposition(matrix):
    n = matrix.shape[0]
    l = np.zeros([matrix.shape[0], matrix.shape[1]])
    u = np.zeros([matrix.shape[0], matrix.shape[1]])
    for i in range(n):
        l[i][i] = 1
        for j in range(i, n):
            for k in range(i):
                u[i][j] -= l[i][k] * u[k][j]
            u[i][j] += matrix[i][j]
        for j in range(i + 1, n):
            for k in range(i):
                l[j][i] -= l[j][k] * u[k][i]
            l[j][i] = (l[j][i] + matrix[j][i]) / u[i][i]
            if u[i][i] == 0:
                print(matrix)
    return l, u


def inverse_upper_matrix(matrix):
    n = matrix.shape[0]
    result = np.zeros([n, n])
    for i in range(n):
        result[i][i] = 1 / matrix[i][i]
        for j in range(i + 1, n):
            for k in range(j):
                result[i][j] -= result[i, k] * matrix[k, j]
            result[i][j] /= matrix[j][j]
    return result


def inverse_down_matrix(matrix):
    matrix = np.transpose(matrix)
    return np.transpose(inverse_upper_matrix(matrix))


def inverse_matrix(matrix):
    lu = LU_decomposition(matrix)
    l_inv = inverse_down_matrix(lu[0])
    u_inv = inverse_upper_matrix(lu[1])
    return np.matmul(u_inv, l_inv)
