#include "../src/matrix/matrix.h"




void test_mem_leaks() {

	for (int iter = 0; iter < 100; iter++) {
		Matrix* matrix = create_matrix(iter, iter);
		free_matrix(matrix);
	}
}


void test_product_mem_leaks() {

	Matrix* matrix1 = create_matrix(100, 100);

	Matrix** results = (Matrix**)malloc(sizeof(Matrix*)* 100);



	for (int iter = 0; iter < 100; iter++) {

		if (iter)
			results[iter] = multiply_matrices(matrix1, results[iter-1]);
		else
			results[iter] = multiply_matrices(matrix1, matrix1);
	}


	for (int iter = 0; iter < 100; iter++) {
		free_matrix(results[iter]);
	}

	free(results);
	free_matrix(matrix1);
}



void test_copy_matrix_mem_leaks() {
	for (int iter = 0; iter < 100; iter++) {
		Matrix* example = create_matrix(iter, iter);
		Matrix* copy = copy_matrix(example);


		free_matrix(example);
		free_matrix(copy);
	}
}