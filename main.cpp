#include "matrix.h"
#include <iostream>
#include <cmath>


#ifndef _WIN32

#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_BACK_COLOR_RED   "\x1b[41m"
#define ANSI_BACK_COLOR_GREEN "\x1b[42m"

#else

#define ANSI_COLOR_RESET

#define ANSI_BACK_COLOR_RED
#define ANSI_BACK_COLOR_GREEN

#endif

//template <typename T>
//void print_test_failed(T value, T expected, const char* message){
//    std::cout << message << '\n';
//    std::cout << "Test failed!\n";
//    std::cout << "Expected: " << expected << ", ";
//    std::cout << "got: " << value << "\n";
//}

//template <typename T>
//void check_equal(T value, T expected, const char* message = ""){
//    if (value != expected){
//        print_test_failed(value, expected, message);
//    }
//}
//printf( ANSI_BACK_COLOR_GREEN "Passed!" ANSI_COLOR_RESET "\n");
//
//#define CHECK_EQUAL(value, expected)                        \
//{                                                           \
//    if (value != expected){                                 \
//        std::cout << "Test failed!\n";                      \
//        std::cout << " Expected: " << expected << ", ";     \
//        std::cout << "got: " << value << "\n";              \
//        return_code = 1;                                    \
//    }                                                       \
//}                                                           \

//    if(value != expected)                                   \
//    {                                                       \
//        printf("Test failed! " STRINGIFY(value)             \
//               " Expected: %i, got %i\n", expected, value); \
//        returnCode = 1;                                     \
//    }                                                       \


bool check_almost_equal(double a, double b, double max_rel_diff = pow(10, -10));
void constructor_test();
void copy_constructor_test(Matrix &&test_matrix);
void plus_test(Matrix &&matrix1, Matrix &&matrix2);
void minus_test(Matrix &&matrix1, Matrix &&matrix2);
void multiply_test(Matrix &&matrix1, Matrix &&matrix2);
void trace_test(Matrix &&matrix_test, double valid_trace);
void determinant_test(Matrix &&matrix_test, double valid_determinant);

void assert_plus(Matrix &matrix1, Matrix &matrix2, Matrix &matrix_valid_result);

void TestPlus_TwoCorrectMatGot_SumReturns();
void TestPlus_TwoIncorrectMatGot_SumReturns();

int return_code = 0;

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

    TestPlus_TwoCorrectMatGot_SumReturns();
    TestPlus_TwoIncorrectMatGot_SumReturns();
    return 0;
}

void print_test_message(const char* message){
    std::cout << message;
}

void print_test_result(int returnCode){
    if (returnCode == 0){
        std::cout << ANSI_BACK_COLOR_GREEN "Test passed" << "\n";
    }
    else{
        std::cout << ANSI_BACK_COLOR_RED "Test failed" << "\n";
    }
}

void TestConstructor_UsualSizeInit_CorrectMatrixReturns(){
    // arrange and act
    return_code = 0;

    Matrix m1(0, 0);
    Matrix m2(1, 1, 1);
    Matrix m3(10, 20, 5);
    Matrix m4(2, 3, IDENTITY);

    // assert
//    CHECK_EQUAL(m1.get_height(), 0);
//    CHECK_EQUAL(m1.get_width(), 0);
//
//    CHECK_EQUAL(m2.get_height(), 1);
//    CHECK_EQUAL(m2.get_width(), 1);
//
//    CHECK_EQUAL(m3.get_height(), 10);
//    CHECK_EQUAL(m3.get_width(), 20);
//
//    CHECK_EQUAL(m2.get_height(), 2);
//    CHECK_EQUAL(m2.get_width(), 3);

    print_test_result(return_code);
}

void TestPlus_TwoCorrectMatGot_SumReturns(){
    print_test_message("Test for operator + for two correct matrices:\t");
    return_code = 0;

    // arrange
    Matrix a1(1, 1, 2);
    Matrix b1(1, 1, 3);

    Matrix a2(2, 3, 4);
    Matrix b2(2, 3, 5);

    Matrix a3(4, 4, IDENTITY);
    Matrix b3(4, 4, IDENTITY);

    // act
    Matrix c1 = a1 + b1;
    Matrix c2 = a2 + b2;
    Matrix c3 = a3 + b3;

    // assert
    assert_plus(a1, b1, c1);
    assert_plus(a2, b2, c2);
    assert_plus(a3, b3, c3);

    print_test_message(ANSI_BACK_COLOR_GREEN"Test passed\n");
}

void TestPlus_TwoIncorrectMatGot_SumReturns(){
    print_test_message("Test for operator + for two incorrect matrices:\t");
    return_code = 0;

    // arrange
    Matrix a1(2, 1, 2);
    Matrix b1(1, 1, 3);

    Matrix a2(5, 3, 4);
    Matrix b2(2, 3, 5);

    Matrix a3(0, 4, IDENTITY);
    Matrix b3(4, 4, IDENTITY);

    // act
    Matrix c1 = a1 + b1;
    Matrix c2 = a2 + b2;
    Matrix c3 = a3 + b3;

    // assert
    assert_plus(a1, b1, c1);
    assert_plus(a2, b2, c2);
    assert_plus(a3, b3, c3);

    print_test_message(ANSI_BACK_COLOR_GREEN"Test passed\n");
}


//bool check_almost_equal(double a, double b, double max_rel_diff){
//    double diff = std::abs(a - b);
//    a = std::abs(a);
//    b = std::abs(b);
//
//    double largest = std::max(a, b);
//    if ((diff <= largest * max_rel_diff) || (a == b)){
//        return true;
//    }
//    return false;
//}
//
//void constructor_test(unsigned int height, unsigned int width, double value){
//    std::cout << "Initializing matrix with" << std::endl;
//    std::cout << "height = " << height << std::endl;
//    std::cout << "width = " << width << std::endl;
//    std::cout << "value = " << value << std::endl;
//
//    Matrix test_matrix(height, width, value);
//    std::cout << test_matrix << std::endl;
//}
//
//void constructor_test(unsigned int height, unsigned int width, MatrixType type){
//    std::cout << "Initializing matrix with" << std::endl;
//    std::cout << "height = " << height << std::endl;
//    std::cout << "width = " << width << std::endl;
//    std::cout << "type = " << type << std::endl;
//
//    std::cout << Matrix(height, width, type) << std::endl;
//}
//
//template <unsigned int lines, unsigned int cols>
//void constructor_test(double (&arr)[lines][cols]){
//    std::cout << "Initializing matrix with" << std::endl;
//    std::cout << "height = " << lines << std::endl;
//    std::cout << "width = " << cols << std::endl;
//
//    std::cout << Matrix((double*) arr, lines, cols) << std::endl;
//}
//
//void copy_constructor_test(Matrix &&test_matrix){
//    std::cout << "Copying matrix with" << std::endl;
//    std::cout << test_matrix << std::endl;
//    Matrix copy_matrix(test_matrix);
//
//    // check equality of elements
//    for (int row = 0; row < copy_matrix.get_height(); row++){
//        for (int col = 0; col < copy_matrix.get_width(); col++){
//            if (copy_matrix.get(row, col) != test_matrix.get(row, col)){
//                std::cout << "ERROR!\n";
//                std::cout << "Not equal";
//            }
//        }
//    }
//
//    // check inequality of data pointers
//    if (copy_matrix.get_width() == 0 || copy_matrix.get_height() == 0){
//        return;
//    }
//    copy_matrix.set(0, 0, std::nan("1"));
//    if (std::isnan(test_matrix.get(0, 0))){
//        std::cout << "ERROR!\n";
//        std::cout << "Data pointers are equal";
//    }
//}
//
void assert_plus(Matrix &matrix1, Matrix &matrix2, Matrix &matrix_valid_result){

    Matrix matrix_sum = matrix1 + matrix2;

    if (matrix1.get_height() == matrix2.get_height() && matrix1.get_width() == matrix2.get_width()){
        if (matrix1.get_height() != matrix_sum.get_height()){
            std::cout << "ERROR!\n";
            std::cout << "Incorrect result size";
            std::cout << ANSI_BACK_COLOR_RED"Test failed";
            exit(1);
        }
        for (int row = 0; row < matrix_sum.get_height(); row++){
            for (int col = 0; col < matrix_sum.get_width(); col++){
                if (matrix_sum.get(row, col) != matrix_valid_result.get(row, col)){
                    std::cout << "ERROR!\n";
                    std::cout << "Value is not correct";
                    std::cout << "Expected:" << matrix_valid_result;
                    std::cout << "Got: " << matrix_sum;
                    std::cout << ANSI_BACK_COLOR_RED"Test failed";
                    exit(1);
                }
            }
        }
    }
    else if (matrix_sum.get_height() != 0 || matrix_sum.get_width() != 0){
        std::cout << "ERROR!\n";
        std::cout << "The matrix" << matrix_sum << "is not null-matrix";
        std::cout << ANSI_BACK_COLOR_RED"Test failed";
        exit(1);
    }
}
//
//void minus_test(Matrix &&matrix1, Matrix &&matrix2){
//
//    Matrix matrix_sub = matrix1 - matrix2;
//
//    std::cout << "Check matrix sub\n";
//    std::cout << "matrix1\n" << matrix1;
//    std::cout << "matrix2\n" << matrix2;
//    std::cout << "matrix_sub\n" << matrix_sub;
//
//    if (matrix1.get_height() == matrix2.get_height() && matrix1.get_width() == matrix2.get_width()){
//        if (matrix1.get_height() != matrix_sub.get_height()){
//            std::cout << "ERROR!\n";
//            std::cout << "Incorrect result size";
//            exit(1);
//        }
//        for (int row = 0; row < matrix_sub.get_height(); row++){
//            for (int col = 0; col < matrix_sub.get_width(); col++){
//                if (matrix_sub.get(row, col) != matrix1.get(row, col) - matrix2.get(row, col)){
//                    std::cout << "ERROR!\n";
//                    std::cout << "Value is not correct";
//                    exit(1);
//                }
//            }
//        }
//    }
//    else if (matrix_sub.get_height() != 0 || matrix_sub.get_width() != 0){
//        std::cout << "ERROR!\n";
//        std::cout << "There are not null-matrix";
//        exit(1);
//    }
//}
//
//void multiply_test(Matrix &&matrix1, Matrix &&matrix2){
//    Matrix matrix_sub = matrix1 - matrix2;
//
//    std::cout << "Check matrix mul\n";
//    std::cout << "matrix1\n" << matrix1;
//    std::cout << "matrix2\n" << matrix2;
//    std::cout << "matrix_mul\n" << matrix_sub;
//
//    // implement!!!
//}
//
//void trace_test(Matrix &&matrix_test, double valid_trace){
//    double checking_trace = matrix_test.tr();
//    std::cout << "Checking trace of matrix\n" << matrix_test;
//    if (!check_almost_equal(checking_trace, valid_trace)){
//        std::cout << "ERROR!" << std::endl;
//        std::cout << "computed trace: " << checking_trace << std::endl;
//        std::cout << "valid trace: " << valid_trace << std::endl;
//        exit(1);
//    }
//}
//
//void determinant_test(Matrix &&matrix_test, double valid_determinant){
//    double checking_determinant = matrix_test.det();
//    std::cout << "Checking determinant of matrix\n" << matrix_test;
//
//    if (!check_almost_equal(checking_determinant, valid_determinant)){
//        if (!(std::isnan(checking_determinant)) && !(std::isnan(valid_determinant))) {
//            std::cout << "ERROR!" << std::endl;
//            std::cout << "computed determinant: " << checking_determinant << std::endl;
//            std::cout << "valid determinant: " << valid_determinant << std::endl;
//            exit(1);
//        }
//    }
//}