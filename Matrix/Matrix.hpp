//
//  Matrix.hpp
//  SLAY Solving
//
//  Created by Виталий Павленко on 07/11/2019.
//  Copyright © 2019 Виталий Павленко. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Rational.h"

class Matrix {
public:
    typedef std::vector<Rational> RationalVector; //Тип для строк матрицы(строки матрицы)
private:
    std::vector<RationalVector> matrix; //вектор из строк
    size_t _rowCount;
    size_t _columCount;
public:
    //**Конструкторы**
    
    //Конструктор с инициализацией
    Matrix(size_t rowsCount, size_t columsCount, Rational init = 0);
    //Это конструктор копирования
    Matrix(const Matrix &anotherMatrix);
    
    //All data will be replaced with 0
    void resize(int rowsCount, int columsCount);
    
    //**Size методы**
    
    //Возвращает длину строк
    size_t rowSize() const;
    //Возвращает длину столбцов
    size_t columSize() const;
    //Возвращает количество столбцов
    size_t columCount() const;
    //Возвращает количество строк
    size_t rowCount() const;
    
    //**Get методы**
    
    //Возвращает вектор, в котором содержится копия строки
    RationalVector getRow(int rowIndex) const;
    //Возвращает вектор, в котором содержится копия столбца
    RationalVector getColum(int columIndex) const;
    
    //**Методы перестановки**
    
    //Меняет строки местами(если передать неправильные индексы, то вернет false)
    bool swapRow(int oldPosition, int newPosition);
    bool swapColum(int oldPosition, int newPosition);

    bool replaceRow(const RationalVector &anotherVector, int position);
    bool replaceColum(const RationalVector &anotherVector, int position);
    
    //**Вспомогательные методы
    void makeZero();
    void fill(Rational value);
    void print() const;
    bool isEmpty(); //возвращает true если рамерность матрицы 0х0
    
    //Доступ к элементам
    Rational& operator()(int row,  int colum) {
        return matrix.at(row).at(colum);
    }
    const Rational& operator()(int row,  int colum) const {
        return matrix.at(row).at(colum);
    }
    
    ~Matrix();
};

Matrix operator*(Rational value,const Matrix &matrix);
Matrix operator*(const Matrix &matrix, Rational value);

//throw functions
Matrix operator*(const Matrix &matrix1, const Matrix &matrix2);
Matrix operator+(const Matrix &matrix1, const Matrix &matrix2);
Matrix operator-(const Matrix &matrix1, const Matrix &matrix2);




//Перечисление, оно содержит только название ошибки
//Я сделал enum, чтобы мне не приходилось самому прописывать описания нашего исключения, посмотри реализацию метода Rational get(int rowPosition, int columPosition) const;
enum MatrixErrorMsg {
    OUT_OF_BOUNDS, //Выход за границы матрицы
    MULTIPLY_MATRIXS_ERROR,
    SUM_MATRIXS_ERROR,
    SUBTRACT_MATRIXS_ERROR,
    ERROR_INDEX
    
    //Здесь может быть много исключений
};

//Тут мы создаем свое собственное исключение, оно наследуется от стандартного
class MatrixExceptions: public std::exception {
private:
    std::string _msg;     //Здесь будет храниться сообщения исключения
public:
    //Конструктор для нашего исключения
    MatrixExceptions(MatrixErrorMsg message) {
        switch (message) { //Здесь может быть много исключений, пока только одно
            case OUT_OF_BOUNDS:
                _msg = "Out of bounds in matrix\n"; //Тут мы прописываем описание нашего исключения
                break;
            case MULTIPLY_MATRIXS_ERROR:
                _msg = "Can not multiply two matrixs\n";
                break;
            case SUM_MATRIXS_ERROR:
                _msg = "Can not sum two matrixs\n";
                break;
            case SUBTRACT_MATRIXS_ERROR:
                _msg = "Can not subtract two matrixs\n";
            case ERROR_INDEX:
                _msg = "Index is under zero or great than matrix sizes\n";
            default:
                break;
        }
    }
    //Это своего рода getter для нашего _msg, просто он переопределяет стандартную функцию вывода сообщения у класса std::exception (Полиморфизм)
    virtual char const* what() const noexcept override {return _msg.c_str();}
};

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);









#endif /* Matrix_hpp */
