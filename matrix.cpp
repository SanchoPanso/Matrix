#include <iostream>
#include <cmath>
#include <cstring>
#include "matrix.h"

static bool check_almost_equal(double a, double b, double max_rel_diff = pow(10, -10));

Matrix::Matrix(unsigned int height,unsigned int width, double value){

    allocate_memory(height, width);

    // if allocating was successful then start initializing
    if (data_1d != nullptr){
        this->height = height;
        this->width = width;
        for (int i = 0; i < height * width; i++) {
            data_1d[i] = value;
        }
    }
}


Matrix::Matrix(unsigned int height, unsigned int width, MatrixType type){

    allocate_memory(height, width);

    // if allocating was successful then start initializing
    if (data_1d != nullptr) {
        this->height = height;
        this->width = width;

        switch (type){
            case IDENTITY: set_identity(); break;
            case ONES: set_ones(); break;
            case RANDOM: set_random(); break;
            case ZEROS:
            default: set_zeros(); break;
        }
    }
}

Matrix::Matrix(double* arr, unsigned int rows, unsigned int cols){

    allocate_memory(rows, cols);

    // if allocating was successful then start initializing
    if (data_1d != nullptr){
        height = rows;
        width = cols;
        memcpy(data_1d, arr, height * width * sizeof(double));
    }
}

Matrix::~Matrix(){
    free_memory();
}

Matrix::Matrix(const Matrix &other){

    allocate_memory(other.height, other.width);

    // if allocating was successful then start copying
    if (data_1d != nullptr) {
        height = other.height;
        width = other.width;
        memcpy(data_1d, other.data_1d, height * width * sizeof(double));
    }
}

Matrix::Matrix(Matrix&& other) noexcept{
    height = other.height;
    width = other.width;

    data_1d = other.data_1d;
    data_2d = other.data_2d;

    other.data_1d = nullptr;
    other.data_2d = nullptr;
}

// overload of operator "=" for copying
Matrix& Matrix::operator= (const Matrix& other){

    // if is the same matrix then return its pointer
    if (this == &other){
        return *this;
    }

    free_memory();
    allocate_memory(height, width);

    // if allocating was successful then start copying
    if (data_1d != nullptr) {
        height = other.height;
        width = other.width;
        memcpy(data_1d, other.data_1d, height * width * sizeof(double));
    }
    return *this;
}

// overload of operator "=" for moving
Matrix& Matrix::operator= (Matrix&& other) noexcept{

    if (this == &other){
        return *this;
    }
    free_memory();

    height = other.height;
    width = other.width;

    data_1d = other.data_1d;
    data_2d = other.data_2d;

    other.data_1d = nullptr;
    other.data_2d = nullptr;
    return *this;
}

// set the value of matrix in corresponding coordinates
// return 0 - success, return 1 - failure
int Matrix::set(unsigned int row, unsigned int col, double value){

    if ((row >= this->height) || (col >= this->width)) {
        return 1;
    }

    this->data_2d[row][col] = value;
    return 0;
}


// get the value from corresponding coordinates
// return 0.0 - row or col out of range
double Matrix::get(unsigned int row, unsigned int col) {

    if ((row >= this->height) || (col >= this->width)) {
        return 0.0;
    }
    return this->data_2d[row][col];
}

// overload of operator "+" for two matrices
Matrix Matrix::operator+ (const Matrix& other){

    // if these matrices are not compatible then return an empty matrix
    if ((height != other.height) || (width != other.width)){
        return Matrix();
    }

    Matrix result(height, width);

    // apply addition for each element
    for (int i = 0; i < height * width; i++){
        result.data_1d[i] = data_1d[i] + other.data_1d[i];
    }
    return result;
}

// overload of operator "-" for two matrices
Matrix Matrix::operator- (const Matrix& other){

    // if these matrices are not compatible then return an empty matrix
    if ((height != other.height) || (width != other.width)){
        return Matrix();
    }

    Matrix result(height, width);

    // apply subtraction for each element
    for (int i = 0; i < height * width; i++){
        result.data_1d[i] = data_1d[i] - other.data_1d[i];
    }
    return result;
}

// overload of operator "*" for two matrices
Matrix Matrix::operator* (const Matrix& other){

    // if these matrices are not compatible then return an empty matrix
    if (width != other.height){
        return Matrix();
    }

    Matrix result(height, other.width);

    // multiply
    for (int row = 0; row < height; row++){
        for (int col = 0; col < other.width; col++){
            result.data_2d[row][col] = 0.0;
            for (int i = 0; i < other.height; i++){
                result.data_2d[row][col] += data_2d[row][i] * other.data_2d[i][col];
            }
        }
    }
    return result;
}

bool Matrix::operator== (const Matrix& other){
    // case of null-matrix
    if (width * height == 0){
        if (other.width * other.height == 0)
            return true;
        return false;
    }
    else{   // if matrices are not null then check dimensions and data
        if (height == other.height && width == other.width){
            for (int i = 0; i < width * height; i++){
                if (!check_almost_equal(data_1d[i], other.data_1d[i]))
                    return false;
            }
            return true;
        }
        else{
            return false;
        }
    }
}

// find trace of matrix
double Matrix::tr(){

    double tr = 0.0;
    for (int i = 0; i < std::min(height, width); i++){
        tr += this->data_2d[i][i];
    }
    return tr;
}

// find determinant of matrix using forward elimination of Gaussian elimination
double Matrix::det(){

    // if the matrix is not square, assume that determinant can not be found
    if (this->width != this->height) {
        return 0.0;
    }
    // if width is zero, computation is not needed, and it can be assumed that det is zero
    if (width == 0){
        return 0.0;
    }
    // create temporary matrix in order not to change values in original matrix
    Matrix tmp_matrix(*this);

    // apply forward elimination (make matrix upper triangular)
    tmp_matrix.apply_forward_elimination();

    // find determinant as multiplying of elements of the main diagonal of the resulting matrix
    double determinant = 1.0;
    for (int diag_elem = 0; diag_elem < width; diag_elem++){
        determinant *= tmp_matrix.data_2d[diag_elem][diag_elem];
    }
    return determinant;
}

// overload of operator "<<" for matrix output
std::ostream& operator<< (std::ostream &out, const Matrix& m){
    for (int row = 0; row < m.height; row++){
        for (int cols = 0; cols < m.width; cols++){
            out << m.data_2d[row][cols] << " ";
        }
        out << "\n";
    }
    return out;
}

// print matrix in std::cout
void Matrix::print(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << data_2d[i][j] << " ";
        }
        std::cout << '\n';
    }
}

void Matrix::set_identity(){
    set_zeros();
    for (int i = 0; i < std::min(height, width); i++){
        data_2d[i][i] = 1.0;
    }
}

void Matrix::set_ones(){
    for (int i = 0; i < height * width; i++){
        data_1d[i] = 1.0;
    }
}

void Matrix::set_zeros(){
    for (int i = 0; i < height * width; i++){
        data_1d[i] = 0.0;
    }
}

void Matrix::set_random(){
    for (int i = 0; i < height * width; i++){
        data_1d[i] = rand();
    }
}

// apply the part of the Gaussian elimination called forward elimination
// in order to transform the square matrix into an upper triangular matrix
void Matrix::apply_forward_elimination(){

    double tmp_row[width];          // temporary array for storing a row during swapping

    double swap_coefficient = 1;    // coef for taking into account that swapping two rows leads
                                    // to change in the sign of the determinant

    // go through each element of the main diagonal
    for (int diag_elem = 0; diag_elem < width; diag_elem++){

        // for increasing accuracy we need to have a diagonal element as more as possible
        // here finding of maximal diagonal element
        int max_diag_elem = diag_elem;
        for (int row = diag_elem + 1; row < height; row++){
            if (std::abs(data_2d[row][diag_elem]) > std::abs(data_2d[row][max_diag_elem])){
                max_diag_elem = diag_elem;
            }
        }

        // if maximal diagonal element is approximately equal to zero
        // then computation has no more sense to continue
        double max_zero_diff = pow(10, -10);
        if (std::abs(data_2d[max_diag_elem][diag_elem]) < max_zero_diff){
            return;
        }

        // maximal diagonal element is not equal to current diagonal element
        // then swap the rows
        if (max_diag_elem > diag_elem){
            swap_coefficient *= -1;
            memcpy(tmp_row, data_2d[max_diag_elem], width * sizeof(double));
            memcpy(data_2d[max_diag_elem], data_2d[diag_elem], width * sizeof(double));
            memcpy(data_2d[diag_elem], tmp_row, width * sizeof(double));
        }

        // go through each row placed bottom diagonal element
        for (int row = diag_elem + 1; row < height; row++){

            // create coefficient that will be multiplied with row,
            // that consists current diagonal element
            double coef = data_2d[row][diag_elem] / data_2d[diag_elem][diag_elem];

            // subtract from considered row another row, that consists current diagonal element
            // and which multiplied with coefficient
            for (int col = diag_elem; col < width; col++){
                data_2d[row][col] -= coef * data_2d[diag_elem][col];
            }
        }
    }

    // accounting the swap_coefficient
    for (int col = 0; col < width; col++){
        data_2d[0][col] *= swap_coefficient;
    }
}

// allocate memory for matrix
void Matrix:: allocate_memory(unsigned int height, unsigned int width){

    // if any dimension is zero then not to allocate memory
    // and leave data_1d and data_2d with default value (nullptr)
    if (width == 0 || height == 0){
        return;
    }

    // try to allocate memory
    try{
        data_1d = new double [height * width];
        data_2d = new double* [height];
    }
    // if something is wrong then free memory and return
    catch (std::bad_alloc const&){
        delete[] data_1d;
        delete[] data_2d;

        data_1d = nullptr;
        data_2d = nullptr;

        return;
    }

    // if allocating was ok, make data_2d a correct 2d array
    for (int row = 0; row < height; row++) {
        data_2d[row] = &data_1d[row * width];
    }
}

// free memory for matrix
void Matrix::free_memory(){

    delete[] data_2d;
    delete[] data_1d;

    height = 0;
    width = 0;
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