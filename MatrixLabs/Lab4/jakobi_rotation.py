import numpy as np
import Lab3.matrix as csr
import math


def solve(matrix: csr.csr_matrix, eps):
    largest = find_largest(matrix)
    j, k, value = largest
    iterations = 0
    while value >= eps:
        iterations += 1
        matrix = rotate(matrix, j, k, eps)
        largest = find_largest(matrix)
        j, k, value = largest
    res = [matrix.get(i, i) for i in range(matrix.n)]
    return res, iterations


def rotate(matrix: csr.csr_matrix, j, k, eps):
    m_jj = matrix.get(j, j)
    m_jk = matrix.get(j, k)
    m_kk = matrix.get(k, k)
    if abs(m_jk) < eps:
        return
    if m_jj == m_kk:
        c = math.sqrt(2) / 2
        s = math.sqrt(2) / 2
    else:
        tau = (m_jj - m_kk) / (2 * m_jk)
        t = math.copysign(1, tau) / (abs(tau) + math.sqrt(1 + tau ** 2))
        c = 1 / math.sqrt(1 + t ** 2)
        s = c * t

    J = csr.csr_matrix(np.zeros([matrix.n, matrix.n]))
    for i in range(matrix.n):
        if i != j and i != k:
            J.set(i, i, 1)
    J.set(j, j, c)
    J.set(k, k, c)
    J.set(j, k, -s)
    J.set(k, j, s)

    matrix = J.transpose().multiply(matrix).multiply(J)
    return matrix


def find_largest(matrix: csr.csr_matrix):
    value = matrix.get(1, 0)
    _j, _k = 1, 0
    for i in range(matrix.n - 1):
        for j in range(i + 1, matrix.n):
            if abs(matrix.get(i, j)) > value:
                value = abs(matrix.get(i, j))
                _j, _k = i, j
    return _j, _k, value
