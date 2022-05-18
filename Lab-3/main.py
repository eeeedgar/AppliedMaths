import numpy as np
import matrix_generation as mg
import sle


def test_jacobi_sequence():
    eps = 1e-10
    size = 100
    for k in range(0, 500, 10):
        a = mg.generate_sequence(size, k)
        b = np.matmul(a, np.array([i for i in range(size)]))
        system = sle.sle(a, np.array([b]))
        ans = system.solve_jacobi(eps)
        print(k, ans.iterations, ans.convergence, ans.error())


test_jacobi_sequence()
