#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../src/output/output.h"
#include "../../include/config.h"



/**
* @brief Структура матрицы
*/
typedef struct {
	int rows; ///< Количество строк
	int cols; ///< Количество столбцов
	MATRIX_TYPE** data; ///< Данные матрицы
} Matrix;


/**
* @brief Создает новую матрицу с заданными размерами
* @param rows Количество строк
* @param cols Количество столбцов
* @return Указатель на созданную матрицу или NULL в случае ошибки
*/
Matrix* create_matrix(int rows, int cols);

/**
* @brief Создаёт идеентичную копию матрицы
* @param source указатель на копируемую матрица
* @return Указатель на cкопированную матрицу или NULL в случае ошибки
*/
Matrix* copy_matrix(const Matrix* source);

/**
* @brief Освобождает память выделенную под матрицу
* @param matrix Указатель на матрицу
*/
void free_matrix(Matrix* matrix);




/**
* @brief Переводит матрицу в формат строки, для сохранение в файл или вывода в стандартный поток
* @param matrix Указатель на матрицу
* @param bufferSize Указатель на вторую матрицу
* @return Строка являющаяся представлением матрицы, первые два числа строки - 
* количество строк и столбцов матрицы далее после символа новой строки идут поочерёдно элементы матрицы
* после каждого элемента идёт пробел, а после каждого крайнего элемента строки помимо пробела идёт символ новой строки.
*/
const char* convert_matrix_to_string(const Matrix* const matrix, size_t bufferSize);

/**
* @brief Выводит матрицу в стандратный поток
* @param matrix Указатель на выводимую матрицу
* @param bufferSize Количество бит, выделяемых на буфер в который будет записываться матрица
*/
void print_matrix(const Matrix* const matrix, size_t bufferSize);

/**
* @brief Сохраняет матрицу в файл
* @param matrix Указатель на сохраняемую матрицу
* @param bufferSize Количество бит, выделяемых на буфер в который будет записываться матрица
* @param filename Название файла в который будет сохранена матрица
*/
int save_matrix_to_file(const Matrix* const matrix, const char* filename, size_t bufferSize);

/**
* @brief Загружает матрицу из файла
* @param filename Название файла в котором находится сохранённая матрица
* @return Указатель на загруженную матрицу
*/
Matrix* load_matrix_from_file(const char* filename);




/**
* @brief Производит сумму матриц
* @param A Указатель на первую матрицу
* @param B Указатель на вторую матрицу
* @return Указатель на матрицу, являющейся суммой матриц A и B
*/
Matrix* add_matrices(const Matrix* const A, const Matrix* const B);


/**
* @brief Производит разность матриц
* @param A Указатель на первую матрицу
* @param B Указатель на вторую матрицу
* @return Указатель на матрицу, являющейся разностью матриц A и B
*/
Matrix* subtract_matrices(const Matrix* const A, const Matrix* const B);


/**
* @brief Производит сумму матриц
* @param A Указатель на первую матрицу
* @param B Указатель на вторую матрицу
* @return Указатель на матрицу, являющейся суммой матриц
*/
Matrix* multiply_matrices(const Matrix* const A, const Matrix* const B);


/**
* @brief Транспонирует матрицу
* @param matrix Указатель на матрицу
* @return Указатель на транспонированную матрицу
*/
Matrix* transpose_matrix(const Matrix* const matrix);


/**
* @brief Находит определитель матрицы
* @param matrix Указатель на матрицу
* @return Число фундаментального типа MATRIX_TYPE, которое соответствует определителю
*/
MATRIX_TYPE determinant(const Matrix* const matrix);