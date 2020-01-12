//
//  Solution.hpp
//  Matrix
//
//  Created by Виталий Павленко on 08/12/2019.
//  Copyright © 2019 Виталий Павленко. All rights reserved.
//

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <vector>
#include "Rational.h"
#include "Matrix.hpp"

//Iterface for solving linear systems of equations
class Solution {
    
public:
    typedef std::vector<Rational> RationalVector;
    virtual RationalVector solve(Matrix matrix) = 0;
};

#endif /* Solution_hpp */
