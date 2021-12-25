#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

typedef enum{
    IDENTITY,
    ONES,
    ZEROS,
    RANDOM,
} MatrixType;

class Matrix{
private:
    unsigned int height = 0;
    unsigned int width = 0;
    double* data_1d = nullptr;
    double** data_2d = nullptr;
public:
    explicit Matrix(unsigned int height = 0, unsigned int width = 0, double value = 0.0);
    Matrix(unsigned int height, unsigned int width, MatrixType type);
    Matrix(double* arr, unsigned int rows, unsigned int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator= (const Matrix& other);
    Matrix& operator= (Matrix&& other) noexcept;
    ~Matrix();
public:
    double get(unsigned int row, unsigned int col);             // return 0.0 - row or col is out of range
    int set(unsigned int row, unsigned int col, double value);  // return 0 - success, return 1 - failure
public:
    unsigned int get_height() const {return height;}
    unsigned int get_width() const {return width;}
public:
    Matrix operator+ (const Matrix& other);     // return Matrix() - not compatible, return result - compatible
    Matrix operator- (const Matrix& other);     // return Matrix() - not compatible, return result - compatible
    Matrix operator* (const Matrix& other);     // return Matrix() - not compatible, return result - compatible
public:
    double tr();    // if height or width is zero - return 0.0
    double det();   // if height or width is zero or the matrix is not square - return 0.0
public:
    void set_identity();
    void set_ones();
    void set_zeros();
    void set_random();
public:
    friend std::ostream& operator<< (std::ostream &out, const Matrix& m);
    void print();
private:
    void apply_forward_elimination();
    void allocate_memory(unsigned int height, unsigned int width);
    void free_memory();
};

#endif //MATRIX_MATRIX_H
