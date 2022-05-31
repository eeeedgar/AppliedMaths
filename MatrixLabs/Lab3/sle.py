import matrix as csr
import numpy as np


def count_difference(x, y):
    res = 0
    for i in range(len(x)):
        temp = abs(x[i] - y[i])
        if temp > res:
            res = temp
    return res


def vector_norm(x):
    result = 0
    for i in range(len(x)):
        result += abs(x[i])
    return result


def matrix_norm(a):
    res = 0
    for i in range(a.shape[0]):
        n = vector_norm(a[i])
        if n > res:
            res = n
    return res


class sle:
    def __init__(self, matrix_a, values):
        self.a_csr = csr.csr_matrix(matrix_a)
        self.values = values
        self.dimension = self.a_csr.n
        self.b_norm = self.b_norma()

    def b_norma(self):
        value = 0
        for i in range(self.dimension):
            v = self.a_csr.get(i, i)
            line_norm = 0
            for j in range(self.dimension):
                if i != j:
                    line_norm += abs(self.a_csr.get(i, j) / v)
            if abs(line_norm) > value:
                value = abs(line_norm)

        return value

    def solve_gauss(self):
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

    def solve_jacobi(self, eps):
        x_curr = [0] * self.dimension
        x_prev = [0] * self.dimension
        for i in range(self.dimension):
            x_curr[i] = self.values[0, i] / self.a_csr.get(i, i)
        difference = 2 * eps
        iterations = 0

        while difference >= eps:
            x_prev = np.copy(x_curr)
            for i in range(self.dimension):
                x_curr[i] = self.values[0, i]
                for j in range(self.dimension):
                    if j != i:
                        x_curr[i] = x_curr[i] - self.a_csr.get(i, j) * x_prev[j]

                x_curr[i] /= self.a_csr.get(i, i)

            if iterations > 50:
                return system_solution(x_curr, x_prev, iterations, False, self.b_norm)
            difference = count_difference(x_curr, x_prev)
            iterations += 1
        return system_solution(x_curr, x_prev, iterations, True, self.b_norm)


class system_solution:
    def __init__(self, x, x_prev, iterations, convergence, b_norm):
        self.x = x
        self.x_prev = x_prev
        self.iterations = iterations
        self.convergence = convergence
        self.b_norm = b_norm

    def error(self):
        return (self.b_norm / (1 - self.b_norm)) * vector_norm(np.array(self.x) - np.array(self.x_prev))
