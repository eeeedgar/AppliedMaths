import unittest
import numpy as np
import sle
import matrix_generation as mg
import random as rnd


def equal_with_eps(first, second, eps):
    if first.shape[0] != second.shape[0] or (len(first.shape) > 1 and len(second.shape) > 1 and first.shape[1] != second.shape[1]):
        return False
    if len(first.shape) > 1 and len(second.shape) > 1:
        for i in range(first.shape[0]):
            for j in range(first.shape[1]):
                if abs(first[i, j] - second[i, j]) >= eps:
                    print(first[i, j], second[i, j])
                    return False
    else:
        for i in range(first.shape[0]):
            if abs(first[i] - second[i]) >= eps:
                print(first[i], second[i])
                return False
    return True


class sle_solve_test(unittest.TestCase):
    def test_sle_gauss(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 10)
            s = mg.generate_system(size, mg.generate_sparse_matrix(size))
            generated_matrix = np.array(s[0])
            b = np.array(s[1])
            system = sle.sle(generated_matrix, np.array([b]))
            ans = np.array(system.solve_gauss())
            ans_np = np.array([s[2]])
            self.assertEqual(equal_with_eps(ans, ans_np, 1e-3), True)

    def test_sle_jacobi(self):
        for i in range(1000):
            rnd.seed()
            size = rnd.randint(3, 3)
            s = mg.generate_system(size, mg.generate_sparse_matrix(size))
            generated_matrix = np.array(s[0])
            b = np.array(s[1])
            system = sle.sle(generated_matrix, np.array([b]))
            ans = system.solve_jacobi(1e-10)
            ans_np = np.array(s[2])
            if ans.convergence:
                self.assertEqual(equal_with_eps(np.array(ans.x), ans_np, 1e-3), True)


if __name__ == '__main__':
    unittest.main()
