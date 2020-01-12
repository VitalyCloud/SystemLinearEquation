#include "Matrix.hpp"
#include <vector>
#include <iostream>

typedef std::vector<Rational> RationalVector;
typedef std::vector<RationalVector> MatrixVector;

Matrix::Matrix(size_t rowsCount, size_t columsCount, Rational init) {
    _rowCount = rowsCount;
    _columCount = columsCount;
    
    if(rowsCount>0 && columsCount>0) {
        matrix.resize(rowsCount);
        for (int i=0; i<matrix.size(); i++) {
            matrix.at(i).resize(columsCount, init);
        }
    }
}

Matrix::Matrix(const Matrix &anotherMatrix) {
    this->matrix = anotherMatrix.matrix;
    _rowCount = anotherMatrix.rowCount();
    _columCount = anotherMatrix.columCount();
}

void Matrix::resize(int rowsCount, int columsCount) {
    if(rowsCount==this->rowCount() && columsCount==this->columCount()) {
        fill(0);
        return;
    }
    
    _rowCount = rowsCount;
    _columCount = columsCount;
    
    if(rowsCount>0 && columsCount>0) {
        matrix.resize(rowsCount);
        for (int i=0; i<matrix.size(); i++) {
            matrix.at(i).resize(columsCount, 0);
        }
        fill(0);
    } else {
        throw MatrixExceptions(MatrixErrorMsg(ERROR_INDEX));
    }
}

bool Matrix::isEmpty() {
    if(rowCount() == 0 || columCount() == 0)
        return true;
    return false;
}

size_t Matrix::rowSize() const {
    return matrix.at(0).size();
    
}
size_t Matrix::columSize() const {
    return matrix.size();
}

size_t Matrix::columCount() const {
    return _columCount;
}
size_t Matrix::rowCount() const {
    return _rowCount;
}

RationalVector Matrix::getRow(int rowIndex) const {
    RationalVector temp;
    if(rowIndex<rowCount()) {
        temp.assign(matrix.at(rowIndex).begin(), matrix.at(rowIndex).end());
    }
    return temp;
}

RationalVector Matrix::getColum(int columIndex) const {
    RationalVector temp;
    if(columIndex < columCount()) {
        for (int i=0; i<columSize(); i++) {
            Rational element = matrix.at(i)[columIndex];
            temp.push_back(element);
        }
    }
    return temp;
}

bool Matrix::swapRow(int oldPosition, int newPosition) {
    if(oldPosition < rowCount() && newPosition < rowCount()) {
        RationalVector temp = matrix.at(oldPosition);
        matrix.at(oldPosition).clear();
        matrix.at(oldPosition).assign(matrix.at(newPosition).begin(), matrix.at(newPosition).end());
        matrix.at(newPosition).clear();
        matrix.at(newPosition).assign(temp.begin(), temp.end());
        return true;
    }
    return false;
}

bool Matrix::swapColum(int oldPosition, int newPosition) {
    if(oldPosition < columCount() && newPosition < columCount()) {
        RationalVector oldVector = getColum(oldPosition);
        RationalVector newVector = getColum(newPosition);
        
        for (int i=0; i<columSize(); i++) {
            (*this)(i, newPosition) = oldVector[i];
            (*this)(i, oldPosition) = newVector[i];
        }
        return true;
    }
    return false;
}

bool Matrix::replaceRow(const RationalVector &anotherVector, int position) {
    if(anotherVector.size() == rowSize()) {
        matrix.at(position).clear();
        matrix.at(position).assign(anotherVector.begin(), anotherVector.end());
        return true;
    }
    return false;
}

bool Matrix::replaceColum(const RationalVector &anotherVector, int position) {
    if(anotherVector.size() == columSize()) {
        for (int i=0; i<columSize(); i++) {
            matrix.at(i)[position] = anotherVector[i];
        }
        return true;
    }
    return false;
}

void Matrix::print() const {
    using namespace std;
    for (auto i=matrix.begin(); i!=matrix.end(); i++) {
        for (auto j=i->begin(); j!=i->end(); j++) {
            cout << *j << "|";
        }
        cout << endl;
    }
}

void Matrix::makeZero() {
    fill(Rational(0));
}

void Matrix::fill(Rational value) {
    for (auto i=matrix.begin(); i!=matrix.end(); i++) {
        for (auto j=i->begin(); j!=i->end(); j++) {
            *j = value;
        }
    }
}

Matrix::~Matrix() {
    
}

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
    using namespace std;
    for (auto i = 0; i < matrix.columSize(); i++) {
        for (auto j = 0; j < matrix.rowSize(); j++) {
            stream << matrix(i,j) << "|";
        }
        stream << endl;
    }
    return stream;
}



Matrix operator*(Rational value,const Matrix &matrix) {
    return matrix*value;
}
Matrix operator*(const Matrix &matrix, Rational value) {
    size_t rowCount = matrix.rowCount();
    size_t columCount = matrix.columCount();
    Matrix result(rowCount, columCount, 0);
    for (int i=0; i<rowCount; i++) {
        for (int j=0; j<columCount; j++) {
            result(i,j) = matrix(i,j)*value;
        }
    }
    return result;
}

Matrix operator*(const Matrix &matrix1, const Matrix &matrix2) {
    size_t rowCount = matrix1.rowCount();
    size_t columCount = matrix2.columCount();
    if(rowCount == columCount) {
        Matrix result(rowCount, columCount, 0);
        for (int row=0; row<matrix1.rowCount(); row++) {
            for (int col=0; col<matrix2.columCount(); col++) {
                for (int inner=0; inner < matrix2.rowCount(); inner++) {
                    result(row,col) += matrix1(row,inner) * matrix2(inner,col);
                }
            }
        }
        return result;
    } else {
        throw MatrixExceptions(MatrixErrorMsg(MULTIPLY_MATRIXS_ERROR));
    }
}

Matrix operator+(const Matrix &matrix1, const Matrix &matrix2) {
    if((matrix1.rowCount() == matrix2.rowCount()) && (matrix1.columCount() == matrix2.columCount())) {
        size_t rowCount = matrix1.rowCount();
        size_t columCount = matrix1.columCount();
        Matrix result(rowCount, columCount, 0);
        for (int i=0; i<rowCount; i++) {
            for (int j=0; j<columCount; j++) {
                result(i,j) += matrix1(i,j) + matrix2(i,j);
            }
        }
        return result;
    } else {
        throw MatrixExceptions(MatrixErrorMsg(SUM_MATRIXS_ERROR));
    }
}
Matrix operator-(const Matrix &matrix1, const Matrix &matrix2) {
    if((matrix1.rowCount() == matrix2.rowCount()) && (matrix1.columCount() == matrix2.columCount())) {
        size_t rowCount = matrix1.rowCount();
        size_t columCount = matrix1.columCount();
        Matrix result(rowCount, columCount, 0);
        for (int i=0; i<rowCount; i++) {
            for (int j=0; j<columCount; j++) {
                result(i,j) += matrix1(i,j) - matrix2(i,j);
            }
        }
        return result;
    } else {
        throw MatrixExceptions(MatrixErrorMsg(SUBTRACT_MATRIXS_ERROR));
    }
}
