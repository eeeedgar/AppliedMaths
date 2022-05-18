import unittest
import random as rnd
import numpy as np
import main as m
import matrix_generation as mg
import matrix as matr

EPS = 1e-3


def equal_with_eps(first, second, eps):
    if first.shape[0] != second.shape[0] or first.shape[1] != second.shape[1]:
        return False
    for i in range(first.shape[0]):
        for j in range(first.shape[1]):
            if abs(first[i, j] - second[i, j]) >= eps:
                print(first[i, j], second[i, j])
                return False
    return True


class csr_test(unittest.TestCase):
    def test_csr_init(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            csr = matr.csr_matrix(generated_matrix)
            mat = csr.get_matrix()
            self.assertEqual(equal_with_eps(generated_matrix, mat, EPS), True)

    def test_csr_insert_in_order(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            csr = matr.csr_matrix(np.zeros([size, size]))
            for j in range(size):
                for k in range(size):
                    if generated_matrix[j, k] != 0:
                        csr.set(j, k, generated_matrix[j, k] - 1)
                        csr.set(j, k, csr.get(j, k) + 1)
            mat = csr.get_matrix()
            self.assertEqual(equal_with_eps(generated_matrix, mat, EPS), True)

    def test_csr_insert_out_of_order(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            csr = matr.csr_matrix(np.zeros([size, size]))
            pairs = [[0, 0]] * size ** 2
            for j in range(size):
                for k in range(size):
                    pairs.insert(rnd.randint(0, size ** 2), [j, k])
            for j in range(len(pairs)):
                csr.set(pairs[j][0], pairs[j][1], generated_matrix[pairs[j][0], pairs[j][1]])
            mat = csr.get_matrix()
            self.assertEqual(equal_with_eps(generated_matrix, mat, EPS), True)

    def test_lu_decomposition(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            csr = matr.csr_matrix(generated_matrix)
            lu = csr.lu_decomposition()
            lu_multiplied = np.matmul(lu[0].get_matrix(), lu[1].get_matrix())
            self.assertEqual(equal_with_eps(lu_multiplied, generated_matrix, EPS), True)

    def test_multiply(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            csr = matr.csr_matrix(generated_matrix)
            lu = csr.lu_decomposition()
            mult = lu[0].multiply(lu[1])
            lu_multiplied = np.matmul(lu[0].get_matrix(), lu[1].get_matrix())
            self.assertEqual(equal_with_eps(lu_multiplied, mult.get_matrix(), EPS), True)

    def test_inverse_triangle_matrix(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            m1 = mg.generate_triangle_reversible_matrix(size, True)
            m2 = mg.generate_triangle_reversible_matrix(size, False)
            generated_upper_matrix = matr.csr_matrix(m1)
            generated_down_matrix = matr.csr_matrix(m2)
            inversion_upper = generated_upper_matrix.inverse_upper_matrix()
            inversion_down = generated_down_matrix.inverse_down_matrix()
            inversion_upper_np = np.linalg.inv(m1)
            inversion_down_np = np.linalg.inv(m2)
            self.assertEqual(equal_with_eps(inversion_upper.get_matrix(), inversion_upper_np, EPS), True)
            self.assertEqual(equal_with_eps(inversion_down.get_matrix(), inversion_down_np, EPS), True)

    def test_inverse_matrix(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            csr = matr.csr_matrix(generated_matrix)
            inverse = csr.inverse_matrix()
            inverse_with_np = np.linalg.inv(generated_matrix)
            self.assertEqual(equal_with_eps(inverse.get_matrix(), inverse_with_np, EPS), True)


if __name__ == '__main__':
    unittest.main()
