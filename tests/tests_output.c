#include "../src/matrix/matrix.h"
#include "../src/output/output.h"

void test_output_to_stdout() {

	Matrix* matrix = create_matrix(100, 100);

	for (int row = 0; row < matrix->rows; row++) {
		for (int col = 0; col < matrix->cols; col++) {
			matrix->data[row][col] = row+col;
		}
	}


	Matrix** results = (Matrix**)malloc(sizeof(Matrix*)*100);


	for (int iter = 0; iter < 100; iter++) {
		if (iter)
			results[iter] = add_matrices(matrix, results[iter-1]);
		else
			results[iter] = add_matrices(matrix, matrix);
	}
	
	for (int iter = 0; iter < 100; iter++) {
		print_matrix(results[iter], 100000);
		printf("\n");
	}


	for (int iter = 0; iter < 100; iter++) {
		free_matrix(results[iter]);
	}

	free(results);
	free_matrix(matrix);
}


void test_output_to_file() {
	Matrix* matrix = create_matrix(100, 100);

	for (int row = 0; row < matrix->rows; row++) {
		for (int col = 0; col < matrix->cols; col++) {
			matrix->data[row][col] = row+col;
		}
	}


	Matrix** results = (Matrix**)malloc(sizeof(Matrix*)*100);


	for (int iter = 0; iter < 100; iter++) {
		if (iter)
			results[iter] = multiply_matrices(matrix, results[iter-1]);
		else
			results[iter] = multiply_matrices(matrix, matrix);
	}
	
	for (int iter = 0; iter < 100; iter++) {
		save_matrix_to_file(results[iter], "output_test.txt", 100000);
	}


	for (int iter = 0; iter < 100; iter++) {
		free_matrix(results[iter]);
	}

	free(results);
	free_matrix(matrix);
}


