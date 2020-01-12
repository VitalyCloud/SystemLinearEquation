//
//  MatrixOperations.cpp
//  Matrix
//
//  Created by Виталий Павленко on 17/11/2019.
//  Copyright © 2019 Виталий Павленко. All rights reserved.
//

#include "MatrixOperations.hpp"
#include <vector>
#include "Rational.h"
#include "Matrix.hpp"

typedef std::vector<Rational> RationalVector;

int MatrixOperations::maxInColum(const Matrix &matrix, int colum) {
    int n = (int)matrix.rowCount();
    Rational max = matrix(colum,colum);
    max = max.abs();
    int maxPos = colum;
    for (int i=colum+1; i<n; i++) {
        Rational element = matrix(i, colum);
        element = element.abs();
        if(element > max) {
            max = element;
            maxPos = i;
        }
    }
    return maxPos;
}

int MatrixOperations::triangulation(Matrix &matrix) {
    unsigned int swapCount = 0;
    int n = (int)matrix.rowCount();
    
    if(n == 0)
        return swapCount;
    
    const int numColum = (int)matrix.columCount();
    for (int i=0; i<n-1; i++) {
        unsigned int imax = maxInColum(matrix, i);
        if(i != imax) {
            matrix.swapRow(i, imax);
            swapCount++;
        }
        
        for(int j=i+1; j<n; j++) {
            Rational mul = -matrix(j,i)/matrix(i,i);
            for (int k=i; k<numColum; k++) {
                matrix(j,k) += matrix(i,k)*mul;
            }
        }
    }
    return swapCount;
}

Rational MatrixOperations::determinant(Matrix matrix, int rowsNum) {
    
    unsigned int swapCount = triangulation(matrix);
    Rational determinant = 1;
    if(swapCount % 2 == 1)
        determinant = -1;
    for (int i=0; i<rowsNum; i++) {
        determinant *= matrix(i,i);
    }
    return determinant;
}



