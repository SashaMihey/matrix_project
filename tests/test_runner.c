#include "../src/matrix/matrix.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>




// прочие тесты
void test_output_to_stdout();
void test_output_to_file();

void test_mem_leaks();
void test_product_mem_leaks();
void test_copy_matrix_mem_leaks();




// тест с CUnit  №1
void FreeMatrixTest() {
    Matrix* A = create_matrix(3, 3);


    free_matrix(A);
    CU_ASSERT(A != NULL);
}


// тест с CUnit №2
void MultiplyMatricesTest() {
    Matrix* A = create_matrix(3,3);
    A->data[0][0] = 3;
    A->data[1][1] = 3;
    A->data[2][2] = 3;

    Matrix* B = create_matrix(3,3);
    B->data[0][0] = 5;
    B->data[1][1] = 5;
    B->data[2][2] = 5;

    Matrix* Product = multiply_matrices(A, B);

    for (int row = 0; row < A->rows; row++) {
        for (int col = 0; col < B->cols; col++) {
            CU_ASSERT((col == row && Product->data[row][row]== 15)  || Product->data[row][col] == 0);
        }
    }

    free_matrix(A);
    free_matrix(B);
    free_matrix(Product);
}



int main() {

    //тест output.h
    //test_output_to_stdout();
    //test_output_to_file();

    //тест matrix.h на утечки памяти
    test_mem_leaks();
    test_product_mem_leaks();
    test_copy_matrix_mem_leaks();

    // тест решения индивидуального задания
    //test_compute_expression();

    // Инициализация CUnit
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Создаём тестовый набор
    CU_pSuite FreeMatrixSuite = CU_add_suite("FreeMatrixSuite", NULL, NULL);
    CU_pSuite MultiplyMatricesSuite = CU_add_suite("MultiplyMatricesSuite", NULL, NULL);
    if (FreeMatrixSuite == NULL || MultiplyMatricesSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    // Добавляем тесты в набор
    if (CU_add_test(FreeMatrixSuite, "free_matrix test", FreeMatrixTest) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(MultiplyMatricesSuite, "multiply_matrices test", MultiplyMatricesTest) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    // Запускаем тесты в режиме базового вывода
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

