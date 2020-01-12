//
//  KramerSolution.hpp
//  Matrix
//
//  Created by Виталий Павленко on 08/12/2019.
//  Copyright © 2019 Виталий Павленко. All rights reserved.
//

#ifndef KramerSolution_hpp
#define KramerSolution_hpp

#include <stdio.h>
#include "Solution.hpp"
#include "MatrixOperations.hpp"

class KramerSolution: public Solution {
public:
    
    RationalVector solve(Matrix matrix) override {
        int rowsNum = (int)matrix.rowCount();
        Rational mainDet = MatrixOperations::determinant(matrix, rowsNum);
        RationalVector result;
        if(mainDet.abs() < 0.0001)
            return result;
        result.resize(rowsNum, 0);
        for (int i=0; i<rowsNum; i++) {
            matrix.swapColum(rowsNum, i);
            result[i] = MatrixOperations::determinant(matrix, rowsNum) / mainDet;
            matrix.swapColum(rowsNum, i);
        }
        return result;
    }
    
};

#endif /* KramerSolution_hpp */
