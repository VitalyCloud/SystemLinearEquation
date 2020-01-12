//
//  MatrixOperations.hpp
//  Matrix
//
//  Created by Виталий Павленко on 17/11/2019.
//  Copyright © 2019 Виталий Павленко. All rights reserved.
//

#ifndef MatrixOperations_hpp
#define MatrixOperations_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include "Rational.h"
#include "Matrix.hpp"

class MatrixOperations {
public:
    typedef std::vector<Rational> RationalVector;
    
    //Find the max element in colum and return the index
    static int maxInColum(const Matrix &matrix, int colum);
    static int triangulation(Matrix &matrix);
    static Rational determinant(Matrix matrix, int rows);
};

#endif /* MatrixOperations_hpp */
