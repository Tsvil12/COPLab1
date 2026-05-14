#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

class Matrix {
private:
    int rows_;
    int cols_;
    double** data_;

public:
    // Конструкторы и деструктор
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();

    // Геттеры
    int GetRows() const;
    int GetCols() const;

    // Операции
    bool EqMatrix(const Matrix& other) const;
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MulNumber(double num);
    void MulMatrix(const Matrix& other);
    Matrix Transpose() const;
    double Determinant() const;

    // Перегрузка операторов
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double num) const;
    bool operator==(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    double& operator()(int i, int j);
    
    // Для печати
    void Print() const;
};

#endif