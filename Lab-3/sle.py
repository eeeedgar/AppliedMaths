import matrix as csr
import numpy as np


class sle:

    def __init__(self, matrix_a, values):
        self.a_csr = csr.csr_matrix(matrix_a)
        self.values = values

    def solve(self):
        lu = self.a_csr.lu_decomposition()
        y = self.solve_gauss_down(lu[0], self.values)
        x = self.solve_gauss_upper(lu[1], y)
        return x

    def solve_gauss_upper(self, a, b):
        x = [0] * self.a_csr.n
        for i in range(self.a_csr.n - 1, -1, -1):
            s = 0
            for j in range(self.a_csr.n - 1, i, -1):
                s += a.get(i, j) * x[j]
            x[i] = (b[0, i] - s) / a.get(i, i)
        return np.array([x])

    def solve_gauss_down(self, a, b):
        x = [0] * self.a_csr.n
        for i in range(self.a_csr.n):
            s = 0
            for j in range(i):
                s += a.get(i, j) * x[j]
            x[i] = (b[0, i] - s) / a.get(i, i)
        return np.array([x])
