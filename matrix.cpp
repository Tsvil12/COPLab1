#include "matrix.hpp"
#include <cmath>
#include <stdexcept>

// Конструктор по умолчанию (3x3)
Matrix::Matrix() : rows_(3), cols_(3) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        data_[i] = new double[cols_]{0};
    }
}

// Параметризированный конструктор
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("Bad size");
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        data_[i] = new double[cols_]{0};
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; j++) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

// Деструктор
Matrix::~Matrix() {
    for (int i = 0; i < rows_; i++) delete[] data_[i];
    delete[] data_;
}

// Геттеры
int Matrix::GetRows() const { return rows_; }
int Matrix::GetCols() const { return cols_; }

// Сравнение
bool Matrix::EqMatrix(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) return false;
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            if (std::fabs(data_[i][j] - other.data_[i][j]) > 1e-9) return false;
    return true;
}

// Сложение
void Matrix::SumMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) 
        throw std::invalid_argument("Wrong dimensions");
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            data_[i][j] += other.data_[i][j];
}

// Вычитание
void Matrix::SubMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) 
        throw std::invalid_argument("Wrong dimensions");
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            data_[i][j] -= other.data_[i][j];
}

// Умножение на число
void Matrix::MulNumber(double num) {
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            data_[i][j] *= num;
}

// Умножение матриц
void Matrix::MulMatrix(const Matrix& other) {
    if (cols_ != other.rows_) throw std::invalid_argument("Wrong dimensions");
    
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < other.cols_; j++)
            for (int k = 0; k < cols_; k++)
                result.data_[i][j] += data_[i][k] * other.data_[k][j];
    *this = result;
}

// Транспонирование
Matrix Matrix::Transpose() const {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            result.data_[j][i] = data_[i][j];
    return result;
}

// Определитель 
double Matrix::Determinant() const {
    if (rows_ != cols_) throw std::invalid_argument("Not square");
    
    if (rows_ == 1) return data_[0][0];
    if (rows_ == 2) return data_[0][0]*data_[1][1] - data_[0][1]*data_[1][0];
    if (rows_ == 3) {
        return data_[0][0] * (data_[1][1]*data_[2][2] - data_[1][2]*data_[2][1])
             - data_[0][1] * (data_[1][0]*data_[2][2] - data_[1][2]*data_[2][0])
             + data_[0][2] * (data_[1][0]*data_[2][1] - data_[1][1]*data_[2][0]);
    }
    throw std::invalid_argument("Only 1x1, 2x2, 3x3 supported");
}

// Операторы
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(*this);
    result.SumMatrix(other);
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(*this);
    result.MulMatrix(other);
    return result;
}

Matrix Matrix::operator*(double num) const {
    Matrix result(*this);
    result.MulNumber(num);
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    return EqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0; i < rows_; i++) delete[] data_[i];
        delete[] data_;
        
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new double*[rows_];
        for (int i = 0; i < rows_; i++) {
            data_[i] = new double[cols_];
            for (int j = 0; j < cols_; j++)
                data_[i][j] = other.data_[i][j];
        }
    }
    return *this;
}

double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) 
        throw std::out_of_range("Index error");
    return data_[i][j];
}

void Matrix::Print() const {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++)
            std::cout << data_[i][j] << " ";
        std::cout << std::endl;
    }
}