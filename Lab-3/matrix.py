class csr_matrix:
    eps = 1e-5
    data = []
    indices = []
    indptr = [1]

    def __init__(self, matrix):
        for i in range(matrix.shape[0]):
            count = 0
            for j in range(matrix.shape[1]):
                if matrix[i, j] != 0:
                    self.data.append(matrix[i, j])
                    self.indices.append(j)
                    count += 1
            self.indptr.append(self.indptr[i] + count)

