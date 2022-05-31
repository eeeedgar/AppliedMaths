import numpy as np


class csr_matrix:
    eps = 1e-5

    def __init__(self, matrix):
        self.n = matrix.shape[0]
        self.m = matrix.shape[1]
        self.data = []
        self.indices = []
        self.l = []
        self.u = []
        self.indptr = [1]
        for i in range(self.n):
            count = 0
            for j in range(self.m):
                if matrix[i, j] != 0:
                    self.data.append(matrix[i, j])
                    self.indices.append(j)
                    count += 1
            self.indptr.append(self.indptr[i] + count)

    def get(self, i, j):
        start = self.indptr[i]
        finish = self.indptr[i + 1]
        for k in range(start, finish):
            if self.indices[k - 1] == j:
                return self.data[k - 1]
        return 0

    def set(self, i, j, value):
        start = self.indptr[i]
        finish = self.indptr[i + 1]
        for k in range(start, finish):
            if self.indices[k - 1] == j:
                if value != 0:
                    self.data[k - 1] = value
                else:
                    del self.data[k - 1]
                    del self.indices[k - 1]
                    for j in range(i + 1, self.n + 1):
                        self.indptr[j] -= 1
                return

        if value == 0:
            return
        self.indices.insert(finish - 1, j)
        self.data.insert(finish - 1, value)

        for k in range(i + 1, self.n + 1):
            self.indptr[k] += 1

    def print(self):
        for i in range(self.n):
            line = ""
            for j in range(self.m):
                line += str(self.get(i, j)) + " "
            print(line)

    def get_matrix(self):
        result = np.zeros([self.n, self.m])
        for i in range(self.n):
            for j in range(self.m):
                result[i, j] = self.get(i, j)
        return result

    def lu_decomposition(self):
        if self.l == [] or self.u == []:
            l_m = csr_matrix(np.zeros([self.n, self.m]))
            u_m = csr_matrix(np.zeros([self.n, self.m]))

            for i in range(self.n):
                l_m.set(i, i, 1)
                for j in range(i, self.n):
                    s = 0
                    for k in range(i):
                        s += l_m.get(i, k) * u_m.get(k, j)
                    u_m.set(i, j, self.get(i, j) - s)
                for j in range(i + 1, self.n):
                    s = 0
                    for k in range(i):
                        s += l_m.get(j, k) * u_m.get(k, i)
                    l_m.set(j, i, (self.get(j, i) - s) / u_m.get(i, i))
            self.l = l_m
            self.u = u_m

        return self.l, self.u

    def transpose(self):
        result = csr_matrix(np.zeros([self.m, self.n]))
        for i in range(self.m):
            for j in range(self.n):
                result.set(i, j, self.get(j, i))
        return result

    def multiply(self, other):
        result = csr_matrix(np.zeros([self.n, other.m]))
        for i in range(self.n):
            for j in range(other.m):
                res = 0
                for k in range(self.m):
                    res += self.get(i, k) * other.get(k, j)
                result.set(i, j, res)
        return result

    def inverse_upper_matrix(self):
        result = csr_matrix(np.zeros([self.n, self.n]))
        for i in range(self.n):
            result.set(i, i, 1 / self.get(i, i))
            for j in range(i + 1, self.n):
                s = 0
                for k in range(j):
                    s -= result.get(i, k) * self.get(k, j)
                result.set(i, j, s / self.get(j, j))
        return result

    def inverse_down_matrix(self):
        matrix = self.transpose()
        return matrix.inverse_upper_matrix().transpose()

    def inverse_matrix(self):
        lu = self.lu_decomposition()
        l_inv = lu[0].inverse_down_matrix()
        u_inv = lu[1].inverse_upper_matrix()
        return u_inv.multiply(l_inv)

    def det(self):
        res = 1
        lu = self.lu_decomposition()
        u = lu[1]
        for i in range(self.n):
            res *= u.get(i, i)
        return res

