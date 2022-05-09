import unittest
import random as rnd
import numpy as np
import main as m
import matrix_generation as mg

EPS = 1e-3


def equal_with_eps(first, second, eps):
    if first.shape[0] != second.shape[0] or first.shape[1] != second.shape[1]:
        return False
    for i in range(first.shape[0]):
        for j in range(first.shape[1]):
            if abs(first[i, j] - second[i, j]) >= eps:
                return False
    return True


class MyTestCase(unittest.TestCase):
    def test_lu_decomposition(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            lu = m.LU_decomposition(generated_matrix)
            lu_multiplied = np.matmul(lu[0], lu[1])
            self.assertEqual(equal_with_eps(lu_multiplied, generated_matrix, EPS), True)

    def test_inverse_triangle_matrix(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_upper_matrix = mg.generate_triangle_reversible_matrix(size, True)
            generated_down_matrix = mg.generate_triangle_reversible_matrix(size, False)
            inversion_upper = m.inverse_upper_matrix(generated_upper_matrix)
            inversion_down = m.inverse_down_matrix(generated_down_matrix)
            inversion_upper_np = np.linalg.inv(generated_upper_matrix)
            inversion_down_np = np.linalg.inv(generated_down_matrix)
            self.assertEqual(equal_with_eps(inversion_upper, inversion_upper_np, EPS), True)
            self.assertEqual(equal_with_eps(inversion_down, inversion_down_np, EPS), True)

    def test_inverse_lu_matrix(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            generated_matrix = mg.generate_sparse_matrix(size)
            inverse = m.inverse_matrix(generated_matrix)
            inverse_with_np = np.linalg.inv(generated_matrix)
            self.assertEqual(equal_with_eps(inverse, inverse_with_np, EPS), True)




if __name__ == '__main__':
    unittest.main()
