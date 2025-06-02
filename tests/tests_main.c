#include "../src/matrix/matrix.h"

Matrix* compute_result(const Matrix* const A, const Matrix* const B, const Matrix* const C, const Matrix* const D) {
	Matrix* C_times_D = multiply_matrices(C, D);
	Matrix* B_transposed = transpose_matrix(B);
	Matrix* temp1 = add_matrices(B_transposed, C_times_D);
	Matrix* res = subtract_matrices(A, temp1);


	free_matrix(C_times_D);
	free_matrix(B_transposed);
	free_matrix(temp1);

	return res;
}

void test_compute_result() {
	for (int iter = 0; iter < 1000; iter++) {
		Matrix* A = create_matrix(iter, iter);
		Matrix* B = create_matrix(iter, iter);
		Matrix* C = create_matrix(iter, iter);
		Matrix* D = create_matrix(iter, iter);

		Matrix* res = compute_result(A, B, C, D);

		free_matrix(A);
		free_matrix(B);
		free_matrix(C);
		free_matrix(D);
		free_matrix(res);
	}
}



