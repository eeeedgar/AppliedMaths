import numpy as np
import matrix_generation as mg
import sle


def test_jacobi_sequence():
    eps = 1e-10
    size = 3
    for k in range(100):
        a = mg.generate_sequence(size, k)
        b = np.matmul(a, np.array([(i + 1) for i in range(size)]))
        system = sle.sle(a, np.array([b]))
        ans = system.solve_jacobi(eps)
        print(ans.x)
        print(np.linalg.solve(a, b))
        print(k, ans.iterations, ans.convergence, ans.error())


def test_gilbert_solution():
    n = [10, 50, 10**2, 10**3, 10**4]
    # n = [3, 10]
    eps = 1e-9
    for k in n:
        a = mg.generate_gilbert_matrix(k)
        b = np.matmul(a, np.array([(i + 1) for i in range(k)]))
        system = sle.sle(a, np.array([b]))
        ans = system.solve_jacobi(eps)
        ans_np = np.linalg.solve(a, b)
        print(k, ans.iterations, ans.convergence, ans.b_norm)


# test_jacobi_sequence()
test_gilbert_solution()
