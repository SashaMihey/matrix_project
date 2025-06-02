#include "matrix.h"


Matrix* create_matrix(int rows, int cols) {
	Matrix* matrix = NULL;
	int success = 1;


	if (rows > 0 && cols > 0) {
		matrix = (Matrix*)malloc(sizeof(Matrix));
		if (matrix) {
			matrix->cols = cols;
			matrix->rows = rows;
			matrix->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*));
			if (matrix->data) {
				for (int row = 0; row < rows && success; row++) {
					matrix->data[row] = (MATRIX_TYPE*)calloc(cols, sizeof(MATRIX_TYPE));
					if (!matrix->data[row])
						success = 0;
				}

				if (!success) {
					for (int row = 0; row < rows; row++)
						if (matrix->data[row])
							free(matrix->data[row]);
					free(matrix->data);
					free(matrix);
					matrix = NULL;
				}
			}
			else {
				free(matrix);
				matrix = NULL;
			}
		}
	}

	return matrix;
}


Matrix* copy_matrix(const Matrix* source) {
	Matrix* copy = NULL;

	if (source) {
		copy = create_matrix(source->rows, source->cols);
		if (copy)
			for (int col = 0; col < source->cols; col++)
				for (int row = 0; row < source->rows; row++)
					copy->data[row][col] = source->data[row][col];
	}

	return copy;
}


void free_matrix(Matrix* matrix) {
	if (matrix) {
		for (int row = 0; row < matrix->rows; row++)
			free(matrix->data[row]);
		free(matrix->data);
		free(matrix);
		matrix = NULL;
	}
}


const char* convert_matrix_to_string(const Matrix* const matrix, size_t bufferSize) {
	char* string = (char*)malloc(bufferSize+1);
	assert(string);

	size_t index = sprintf(string, "%d %d\n", matrix->rows, matrix->cols);

	for (int row = 0; row < matrix->rows; row++) {
		for (int col = 0; col < matrix->cols; col++) {
			index += sprintf(string + index, "%lf ", (double)matrix->data[row][col]);
		}
		index += sprintf(string + index,"\n");
	}

	string[bufferSize - 1] = '\0';

	return (const char*)string;
}



void print_matrix(const Matrix* const matrix, size_t bufferSize) {
	const char* str_matrix = convert_matrix_to_string(matrix, bufferSize);

	output_to_stdout(str_matrix);

	free((char*)str_matrix);
}


int save_matrix_to_file(const Matrix* const matrix, const char* filename, size_t bufferSize) {
	const char* str_matrix = convert_matrix_to_string(matrix, bufferSize);

	int res = output_to_file(filename, str_matrix);

	free((char*)str_matrix);

	return res;
}



Matrix* load_matrix_from_file(const char* filename) {
	FILE* file = fopen(filename, "r");

	int rows, cols;

	fscanf(file, "%d %d\n", &rows, &cols);


	Matrix* matrix = create_matrix(rows, cols);


	assert(matrix);

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			double var;

			fscanf(file, "%lf ", &var);
			*((matrix->data)[row] + col) = (MATRIX_TYPE)var;
		}
	}

	fclose(file);

	return matrix;
}



Matrix* add_matrices(const Matrix* const A, const Matrix* const B) {

	int rows = (A->rows > B->rows)? A->rows : B->rows;
	int cols = (A->cols > B->cols)? A->cols : B->cols;

	Matrix* result = create_matrix(rows, cols);

	if (result != NULL) {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {

				MATRIX_TYPE a = (row < A->rows && col < A->cols) ? A->data[row][col] : 0;
				MATRIX_TYPE b = (row < B->rows && col < B->cols) ? B->data[row][col] : 0;

				result->data[row][col] = a + b;
			}
		}
	}

	return result;
}


Matrix* subtract_matrices(const Matrix* const A, const Matrix* const B) {

	int rows = (A->rows > B->rows)? A->rows : B->rows;
	int cols = (A->cols > B->cols)? A->cols : B->cols;

	Matrix* result = create_matrix(rows, cols);

	if (result != NULL) {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {

				MATRIX_TYPE a = (row < A->rows && col < A->cols) ? A->data[row][col] : 0;
				MATRIX_TYPE b = (row < B->rows && col < B->cols) ? B->data[row][col] : 0;

				result->data[row][col] = a - b;
			}
		}
	}

	return result;
}


Matrix* multiply_matrices(const Matrix* const A, const Matrix* const B) {
	if (A->cols != B->rows)
		return NULL;

	Matrix* result = create_matrix(A->rows, B->cols);

	if (result != NULL) {
		for (int row = 0; row < A->rows; row++) {
			for (int col = 0; col < B->cols; col++) {
				for (int iter = 0; iter < A->cols; iter++) {
					result->data[row][col] = A->data[row][iter] * B->data[iter][col];
				}
			}
		}
	}
	return result;
}



Matrix* transpose_matrix(const Matrix* const matrix) {
	Matrix* result = create_matrix(matrix->cols, matrix->rows);

	if (result != NULL) 
		for (int row = 0; row < matrix->rows; row++) 
			for (int col = 0; col < matrix->cols; col++) 
				result->data[col][row] = matrix->data[row][col];


	return result;
}



MATRIX_TYPE determinant(const Matrix* const matrix) {
	assert(matrix->cols == matrix->rows && matrix->rows + matrix->cols >= 2);

	if (matrix->cols == 2) {
		return matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
	}
	else {
		MATRIX_TYPE res = 0;

		for (int iter = 0; iter < matrix->cols; iter++) {
			Matrix* minor = create_matrix(matrix->rows - 1, matrix->cols - 1);

			assert(minor != NULL);

			for (int row = 0; row < minor->rows; row++) {
				for (int col = 0; col < minor->cols; col++) {
					minor->data[row][col] = matrix->data[row + 1][(col >= iter) ? col + 1 : col];
				}
			}
			res += matrix->data[0][iter] * (2 * (iter % 2) - 1) * determinant(minor);
		}
		return res;
	}
}