#include "matrix.h"
#include <iostream>
#include <cmath>

bool check_almost_equal(double a, double b, double max_rel_diff = pow(10, -10));
void constructor_test(unsigned int height = 0, unsigned int width = 0, double value = 0.0);
void constructor_test(unsigned int height, unsigned int width, MatrixType type);
template <unsigned int lines, unsigned int cols>
void constructor_test(double (&arr)[lines][cols]);
void copy_constructor_test(Matrix &&test_matrix);
void plus_test(Matrix &&matrix1, Matrix &&matrix2);
void minus_test(Matrix &&matrix1, Matrix &&matrix2);
void multiply_test(Matrix &&matrix1, Matrix &&matrix2);
void trace_test(Matrix &&matrix_test, double valid_trace);
void determinant_test(Matrix &&matrix_test, double valid_determinant);


double test_array1[2][2] = {{1, 2},
                            {4, 3}};
double test_array2[2][2] = {{2, 2},
                            {2, 2}};
double test_array3[3][3] = {{1, 0, 0},
                            {0, 1, 0},
                            {0, 0, 1}};
double test_array4[2][3] = {{1, 2, 3},
                            {0, 1, 0}};
double test_array5[3][3] = {{4, 2, 2},
                            {2, 3, 1},
                            {7, 3, 1}};
double test_array6[4][4] = {{7, 11, 9, 10},
                            {6, 6, 5, 5},
                            {1, 2, 1, 2},
                            {3, 4, 3, 4}};


int main() {
    constructor_test(0, 0, 0);
    constructor_test(-2, -3, 5);
    constructor_test(2, 2, 2);
    constructor_test(2, 2, IDENTITY);
    constructor_test(test_array2);

    copy_constructor_test(Matrix(1, 2, 3));
    copy_constructor_test(Matrix(3, 3, IDENTITY));

    plus_test(Matrix(), Matrix());
    plus_test(Matrix(1, 2, 3), Matrix(2, 2, 1));
    plus_test(Matrix(4, 4, 4), Matrix(4, 4, IDENTITY));

    minus_test(Matrix(), Matrix());
    minus_test(Matrix(1, 2, 3), Matrix(2, 2, 1));
    minus_test(Matrix(4, 4, 4), Matrix(4, 4, IDENTITY));

    trace_test(Matrix(), 0);
    trace_test(Matrix(1, 1, 1), 1);
    trace_test(Matrix(2, 2, 2), 4);
    trace_test(Matrix(2, 4, 4), 8);
    trace_test(Matrix((double*) test_array1, 2, 2), 4);

    determinant_test(Matrix(), 0);
    determinant_test(Matrix(3, 3, IDENTITY), 1);
    determinant_test(Matrix(1, 1, 1), 1);
    determinant_test(Matrix(2, 2, 3), 0);
    determinant_test(Matrix(2, 4, 4), std::nan("1"));
    determinant_test(Matrix((double*) test_array1, 2, 2), -5);
    determinant_test(Matrix((double*) test_array5, 3, 3), -20);
    determinant_test(Matrix((double*) test_array6, 4, 4), 6);

    return 0;
}

bool check_almost_equal(double a, double b, double max_rel_diff){
    double diff = std::abs(a - b);
    a = std::abs(a);
    b = std::abs(b);

    double largest = std::max(a, b);
    if ((diff <= largest * max_rel_diff) || (a == b)){
        return true;
    }
    return false;
}

void constructor_test(unsigned int height, unsigned int width, double value){
    std::cout << "Initializing matrix with" << std::endl;
    std::cout << "height = " << height << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "value = " << value << std::endl;

    Matrix test_matrix(height, width, value);
    std::cout << test_matrix << std::endl;
}

void constructor_test(unsigned int height, unsigned int width, MatrixType type){
    std::cout << "Initializing matrix with" << std::endl;
    std::cout << "height = " << height << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "type = " << type << std::endl;

    std::cout << Matrix(height, width, type) << std::endl;
}

template <unsigned int lines, unsigned int cols>
void constructor_test(double (&arr)[lines][cols]){
    std::cout << "Initializing matrix with" << std::endl;
    std::cout << "height = " << lines << std::endl;
    std::cout << "width = " << cols << std::endl;

    std::cout << Matrix((double*) arr, lines, cols) << std::endl;
}

void copy_constructor_test(Matrix &&test_matrix){
    std::cout << "Copying matrix with" << std::endl;
    std::cout << test_matrix << std::endl;
    Matrix copy_matrix(test_matrix);

    // check equality of elements
    for (int row = 0; row < copy_matrix.get_height(); row++){
        for (int col = 0; col < copy_matrix.get_width(); col++){
            if (copy_matrix.get(row, col) != test_matrix.get(row, col)){
                std::cout << "ERROR!\n";
                std::cout << "Not equal";
            }
        }
    }

    // check inequality of data pointers
    if (copy_matrix.get_width() == 0 || copy_matrix.get_height() == 0){
        return;
    }
    copy_matrix.set(0, 0, std::nan("1"));
    if (std::isnan(test_matrix.get(0, 0))){
        std::cout << "ERROR!\n";
        std::cout << "Data pointers are equal";
    }
}

void plus_test(Matrix &&matrix1, Matrix &&matrix2){

    Matrix matrix_sum = matrix1 + matrix2;

    std::cout << "Check matrix sum\n";
    std::cout << "matrix1\n" << matrix1;
    std::cout << "matrix2\n" << matrix2;
    std::cout << "matrix_sum\n" << matrix_sum;

    if (matrix1.get_height() == matrix2.get_height() && matrix1.get_width() == matrix2.get_width()){
        if (matrix1.get_height() != matrix_sum.get_height()){
            std::cout << "ERROR!\n";
            std::cout << "Incorrect result size";
            exit(1);
        }
        for (int row = 0; row < matrix_sum.get_height(); row++){
            for (int col = 0; col < matrix_sum.get_width(); col++){
                if (matrix_sum.get(row, col) != matrix1.get(row, col) + matrix2.get(row, col)){
                    std::cout << "ERROR!\n";
                    std::cout << "Value is not correct";
                    exit(1);
                }
            }
        }
    }
    else if (matrix_sum.get_height() != 0 || matrix_sum.get_width() != 0){
        std::cout << "ERROR!\n";
        std::cout << "There are not null-matrix";
        exit(1);
    }
}

void minus_test(Matrix &&matrix1, Matrix &&matrix2){

    Matrix matrix_sub = matrix1 - matrix2;

    std::cout << "Check matrix sub\n";
    std::cout << "matrix1\n" << matrix1;
    std::cout << "matrix2\n" << matrix2;
    std::cout << "matrix_sub\n" << matrix_sub;

    if (matrix1.get_height() == matrix2.get_height() && matrix1.get_width() == matrix2.get_width()){
        if (matrix1.get_height() != matrix_sub.get_height()){
            std::cout << "ERROR!\n";
            std::cout << "Incorrect result size";
            exit(1);
        }
        for (int row = 0; row < matrix_sub.get_height(); row++){
            for (int col = 0; col < matrix_sub.get_width(); col++){
                if (matrix_sub.get(row, col) != matrix1.get(row, col) - matrix2.get(row, col)){
                    std::cout << "ERROR!\n";
                    std::cout << "Value is not correct";
                    exit(1);
                }
            }
        }
    }
    else if (matrix_sub.get_height() != 0 || matrix_sub.get_width() != 0){
        std::cout << "ERROR!\n";
        std::cout << "There are not null-matrix";
        exit(1);
    }
}

void multiply_test(Matrix &&matrix1, Matrix &&matrix2){
    Matrix matrix_sub = matrix1 - matrix2;

    std::cout << "Check matrix mul\n";
    std::cout << "matrix1\n" << matrix1;
    std::cout << "matrix2\n" << matrix2;
    std::cout << "matrix_mul\n" << matrix_sub;

    // implement!!!
}

void trace_test(Matrix &&matrix_test, double valid_trace){
    double checking_trace = matrix_test.tr();
    std::cout << "Checking trace of matrix\n" << matrix_test;
    if (!check_almost_equal(checking_trace, valid_trace)){
        std::cout << "ERROR!" << std::endl;
        std::cout << "computed trace: " << checking_trace << std::endl;
        std::cout << "valid trace: " << valid_trace << std::endl;
        exit(1);
    }
}

void determinant_test(Matrix &&matrix_test, double valid_determinant){
    double checking_determinant = matrix_test.det();
    std::cout << "Checking determinant of matrix\n" << matrix_test;

    if (!check_almost_equal(checking_determinant, valid_determinant)){
        if (!(std::isnan(checking_determinant)) && !(std::isnan(valid_determinant))) {
            std::cout << "ERROR!" << std::endl;
            std::cout << "computed determinant: " << checking_determinant << std::endl;
            std::cout << "valid determinant: " << valid_determinant << std::endl;
            exit(1);
        }
    }
}

