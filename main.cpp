#include "matrix.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "========== МАТРИЦЫ ==========\n" << endl;
    
    // Создание матриц
    Matrix A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;
    
    Matrix B(2, 2);
    B(0, 0) = 5; B(0, 1) = 6;
    B(1, 0) = 7; B(1, 1) = 8;
    
    cout << "Матрица A:" << endl;
    A.Print();
    
    cout << "\nМатрица B:" << endl;
    B.Print();
    
    // Сложение
    Matrix C = A + B;
    cout << "\nA + B:" << endl;
    C.Print();
    
    // Вычитание
    Matrix D = A - B;
    cout << "\nA - B:" << endl;
    D.Print();
    
    // Умножение на число
    Matrix E = A * 2;
    cout << "\nA * 2:" << endl;
    E.Print();
    
    // Умножение матриц
    Matrix F = A * B;
    cout << "\nA * B:" << endl;
    F.Print();
    
    // Транспонирование
    Matrix T = A.Transpose();
    cout << "\nТранспонированная A:" << endl;
    T.Print();
    
    // Определитель
    cout << "\nОпределитель A = " << A.Determinant() << endl;
    
    // Сравнение
    cout << "\nA == B? " << (A == B ? "Да" : "Нет") << endl;
    
    return 0;
}