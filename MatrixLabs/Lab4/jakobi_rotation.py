import numpy as np
import Lab3.matrix as csr
import math


def solve(matrix: csr.csr_matrix, eps):
    largest = findLargest(matrix)
    j, k, value = largest
    rotations = 0
    iterations = 0
    while value >= eps:
        iterations += 1
        # for j in range(matrix.n - 1):
        #     for k in range(j + 1, matrix.n):
        rotate(matrix, j, k, eps)
        rotations += 1
        largest = findLargest(matrix)
        j, k, value = largest
        print("j = " + str(j) + " k = " + str(k) + " value: " + str(value))
    res = [matrix.get(i, i) for i in range(matrix.n)]
    return res, iterations, rotations


def rotate(matrix: csr.csr_matrix, j, k, eps):
    m_jj = matrix.get(j, j)
    m_jk = matrix.get(j, k)
    m_kk = matrix.get(k, k)
    if abs(matrix.get(j, k)) < eps:
        return
    if matrix.get(j, j) == matrix.get(k, k):
        c = math.sqrt(2) / 2
        s = math.sqrt(2) / 2
    else:
        tau = (matrix.get(j, j) - matrix.get(k, k)) / (2 * matrix.get(j, k))
        t = math.copysign(1, tau) / (abs(tau) + math.sqrt(1 + tau ** 2))
        c = 1 / math.sqrt(1 + t ** 2)
        s = c * t
    # s = m_jj / (m_jj ** 2 + m_jk ** 2) ** .5
    # c = m_jk / (m_jj ** 2 + m_jk ** 2) ** .5
    # print("c = " + str(m_jj / (m_jj ** 2 + m_jk ** 2) ** .5) + " s = " +
    #       str(m_jk / (m_jj ** 2 + m_jk ** 2) ** .5))
    # print("c = " + str(c) + " s = " + str(s))

    matrix.set(j, j, c ** 2 * m_jj - 2 * s * c * m_jk + s ** 2 * m_kk)
    matrix.set(k, k, s ** 2 * m_jj + 2 * s * c * m_jk + c ** 2 * m_kk)
    # el = (c ** 2 - s ** 2) * m_jk + s * c * (m_kk - m_jj)
    # print(el)
    el = 0
    matrix.set(j, k, el)
    matrix.set(k, j, el)
    temp1 = [0] * matrix.n
    temp2 = [0] * matrix.n
    for m in range(matrix.n):
        if m != j and m != k:
            temp1[m] = c * matrix.get(j, m) - s * matrix.get(k, m)
            temp2[m] = s * matrix.get(j, m) + c * matrix.get(k, m)
    for m in range(matrix.n):
        if m != k and m != j:
            matrix.set(j, m, temp1[m])
            matrix.set(m, j, temp1[m])
            matrix.set(k, m, temp2[m])
            matrix.set(m, k, temp2[m])
    print(matrix.get_matrix())


def findLargest(matrix: csr.csr_matrix):
    value = matrix.get(1, 0)
    _j, _k = 1, 0
    for i in range(matrix.n - 1):
        for j in range(i + 1, matrix.n):
            if i != j and abs(matrix.get(i, j)) > value:
                value = abs(matrix.get(i, j))
                _j, _k = i, j
    return _j, _k, value
