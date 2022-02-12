#include "../matrix.h"
#include <cmath>
#include <iostream>

#ifndef _WIN32
#   define ANSI_COLOR_RESET   "\x1b[0m"
#   define ANSI_BACK_COLOR_RED   "\x1b[41m"
#   define ANSI_BACK_COLOR_GREEN "\x1b[42m"
#else
#   define ANSI_COLOR_RESET
#   define ANSI_BACK_COLOR_RED
#   define ANSI_BACK_COLOR_GREEN
#endif

#define TO_STR(value) #value

#define CHECK_EQUAL(got_value, expected_value){                         \
    if (got_value != expected_value){                                   \
        std::cout << "\nGot: " << TO_STR(got_value) << '\n';            \
        std::cout << "Expected: " << TO_STR(expected_value) << '\n';    \
        return 1;                                                       \
    }                                                                   \
}

#define CHECK_ALMOST_EQUAL(got_value, expected_value){                  \
    if (!check_almost_equal((got_value), (expected_value))){            \
        std::cout << "\nGot: " << got_value << '\n';                    \
        std::cout << "Expected: " << expected_value << '\n';            \
        return 1;                                                       \
    }                                                                   \
}

#define RUN_TEST(test, message){                        \
    printf(message);                                    \
    int retval = test();                                \
    if (retval == 0){                                   \
        printf("\t");                                   \
        printf(ANSI_BACK_COLOR_GREEN"Passed\n");        \
    }                                                   \
    else{                                               \
        printf("\t");                                   \
        printf(ANSI_BACK_COLOR_RED"Failed\n");          \
    }                                                   \
}


#define CHECK_PLUS(a, b, result)                                                            \
{                                                                                           \
    for (int row = 0; row < a.get_height(); row++)                                          \
        for (int col = 0; col < a.get_width(); col++)                                       \
            CHECK_EQUAL(check_almost_equal(a.get(row, col) + b.get(row, col),               \
            result.get(row, col)), true);                                                   \
}                                                                                           \


int constructor_test();
int operator_equals_test();
int operator_plus_test();
int trace_test();
int determinant_test();

bool check_almost_equal(double a, double b, double max_rel_diff = 1e-10);


int main(){
    RUN_TEST(constructor_test, "Constructor test: ");
    RUN_TEST(operator_equals_test, "Operator== test: ");
    RUN_TEST(operator_plus_test, "Operator+ test: ");
    RUN_TEST(trace_test, "Trace test: ")
    RUN_TEST(determinant_test, "Determinant test: ");



    return 0;
}

int constructor_test(){
    Matrix m1;
    CHECK_EQUAL(m1.get_height(), 0);
    CHECK_EQUAL(m1.get_width(), 0);

    Matrix m2(2, 0);
    CHECK_EQUAL(m2.get_height(), 0);
    CHECK_EQUAL(m2.get_width(), 0);

    Matrix m3(3, 2, 3);
    CHECK_EQUAL(m3.get_height(), 3);
    CHECK_EQUAL(m3.get_width(), 2);
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 2; col++)
            CHECK_EQUAL(m3.get(row, col), 3);

    Matrix m4(3, 3, IDENTITY);
    CHECK_EQUAL(m4.get_height(), 3);
    CHECK_EQUAL(m4.get_width(), 3);
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            CHECK_EQUAL(m4.get(row, col), (row == col ? 1 : 0));
//
//    Matrix m5(-2, -1, 5);
//    CHECK_EQUAL(m5.get_height(), 0);
//    CHECK_EQUAL(m5.get_width(), 0);

    return 0;
}

int operator_equals_test(){
    CHECK_EQUAL((Matrix(0, 0) == Matrix(0, 0)), true);
    CHECK_EQUAL((Matrix(0, 0) == Matrix(1, 2)), false);
    CHECK_EQUAL((Matrix(1, 3) == Matrix(0, 1)), false);
    CHECK_EQUAL((Matrix(2, 2, 2) == Matrix(3, 3, 2)), false);
    CHECK_EQUAL((Matrix(4, 3, 5) == Matrix(4, 3, 5)), true);
    CHECK_EQUAL((Matrix(4, 4, IDENTITY) == Matrix(4, 4, IDENTITY)), true);

    return 0;
}

int operator_plus_test(){
    {
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
        CHECK_PLUS(a1, b1, c1);
        CHECK_PLUS(a2, b2, c2);
        CHECK_PLUS(a3, b3, c3);
    }
    {
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
        CHECK_EQUAL(c1.get_height(), 0);
        CHECK_EQUAL(c1.get_width(), 0);

        CHECK_EQUAL(c2.get_height(), 0);
        CHECK_EQUAL(c2.get_width(), 0);

        CHECK_EQUAL(c3.get_height(), 0);
        CHECK_EQUAL(c3.get_width(), 0);
    }

    return 0;
}

int trace_test(){

    double test_array1[2][2] = {{1, 2},
                                {4, 3}};

    double test_array2[3][3] = {{4, 2, 2},
                                {2, 3, 1},
                                {7, 3, 1}};

    double trace1 = Matrix().tr();
    double trace2 = Matrix(1, 1, 1).tr();
    double trace3 = Matrix(2, 2, 2).tr();
    double trace4 = Matrix(2, 4, 4).tr();
    double trace5 = Matrix(2, 2, (double*) test_array1).tr();
    double trace6 = Matrix(3, 3, (double*) test_array2).tr();

    CHECK_ALMOST_EQUAL(trace1, 0.);
    CHECK_ALMOST_EQUAL(trace2, 1.);
    CHECK_ALMOST_EQUAL(trace3, 4.);
    CHECK_ALMOST_EQUAL(trace4, 8.);
    CHECK_ALMOST_EQUAL(trace5, 4.);
    CHECK_ALMOST_EQUAL(trace6, 8.);

    return 0;
}

int determinant_test(){
    double test_array1[2][2] = {{1, 2},
                                {4, 3}};
    double test_array2[3][3] = {{4, 2, 2},
                                {2, 3, 1},
                                {7, 3, 1}};
    double test_array3[4][4] = {{7, 11, 9, 10},
                                {6, 6, 5, 5},
                                {1, 2, 1, 2},
                                {3, 4, 3, 4}};

    CHECK_EQUAL(check_almost_equal(Matrix().det(), 0.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(3, 3, IDENTITY).det(), 1.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(1, 1, 1).det(), 1.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(2, 2, 3).det(), 0.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(2, 4, 4).det(), 0.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(2, 2, (double*) test_array1).det(), -5.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(3, 3, (double*) test_array2).det(), -20.), true);
    CHECK_EQUAL(check_almost_equal(Matrix(4, 4, (double*) test_array3).det(), 6.), true);

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
