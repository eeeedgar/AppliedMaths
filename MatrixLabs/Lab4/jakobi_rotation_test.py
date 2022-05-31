import unittest
import jakobi_rotation as jr
import Lab3.matrix as csr
import numpy as np
import Lab3.matrix_generation as mg

eps = 1e-10


def are_equal_with_eps(a: np.array, b: np.array, e):
    for i in range(a.shape[0]):
        if (abs(a[i] - b[i])) > e:
            return False
    return True


class JakobiSolveTest(unittest.TestCase):
        def test_solve_int(self):
            generated = np.array([
                [2, 0, 0],
                [0, 10, 2],
                [0, 2, 10]])
            csr_matrix = csr.csr_matrix(generated)
            solution_jr = np.sort(jr.solve(csr_matrix, eps)[0])
            solution_np = np.sort(np.linalg.eigh(generated)[0])
            self.assertEqual(are_equal_with_eps(solution_np, solution_jr, 1e-5), True)

        def test_solve_rand(self):
            for i in range(1000):
                generated = mg.generate_symmetric_matrix(3)
                csr_matrix = csr.csr_matrix(generated)
                solution_jr = np.sort(jr.solve(csr_matrix, eps)[0])
                solution_np = np.sort(np.linalg.eigh(generated)[0])
                print(solution_jr)
                self.assertEqual(are_equal_with_eps(solution_np, solution_jr, 1e-5), True)


if __name__ == '__main__':
    unittest.main()