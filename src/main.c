#include "matrix/matrix.h"
#include "output/output.h"


Matrix* compute_result(const Matrix* const A, const Matrix* const B, const Matrix* const C, const Matrix* const D) {
	Matrix* B_transposed = transpose_matrix(B);
	Matrix* temp1 = add_matrices(B_transposed, C);
	Matrix* temp2 = multiply_matrices(temp1, D);

	Matrix* res = subtract_matrices(A, temp2);

	free_matrix(B_transposed);
	free_matrix(temp1);
	free_matrix(temp2);

	return res;
}


int main() {

	Matrix* A = create_matrix(1, 3);
	A->data[0][0] = 1;
	A->data[0][1] = -5;
	A->data[0][2] = 1.3;


	Matrix* B = create_matrix(3, 1);
	B->data[0][0] = 8;
	B->data[1][0] = -0.23;
	B->data[2][0] = 7;


	Matrix* C = create_matrix(1, 3);
	C->data[0][0] = 1;
	C->data[0][1] = 0;
	C->data[0][2] = -13;


	Matrix* D = create_matrix(3, 2);
	D->data[0][0] = 0;
	D->data[0][1] = 9;
	D->data[1][0] = 0;
	D->data[1][1] = -14;
	D->data[2][0] = 7;
	D->data[2][1] = 3;


	Matrix* res = compute_result(A, B, C, D);


	print_matrix(res, 94);

	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(D);
	free_matrix(res);


	return 0;
}

