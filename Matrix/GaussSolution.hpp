//
//  GaussSolution.hpp
//  Matrix
//
//  Created by Виталий Павленко on 08/12/2019.
//  Copyright © 2019 Виталий Павленко. All rights reserved.
//

#ifndef GaussSolution_hpp
#define GaussSolution_hpp

#include <stdio.h>
#include "Solution.hpp"
#include "MatrixOperations.hpp"

class GaussSolution: public Solution {
public:
    
    //Solve the linear equations
    RationalVector solve(Matrix matrix) override {
        int n = (int)matrix.rowCount();
        RationalVector solution;
        solution.resize(n, 0);
        
        MatrixOperations::triangulation(matrix);
        
        for (int i=n-1; i>=0; i--) {
            if(matrix(i,i).abs() < 0.0001) {
                return solution;
            }
            
            solution[i] = matrix(i,n)/matrix(i,i);
            
            for (int j=0; j<i; j++) {
                matrix(j,n) -= matrix(j,i)*solution[i];
            }
            
        }
        return solution;
    }
};

#endif /* GaussSolution_hpp */
