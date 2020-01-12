#include <iostream>
#include <vector>


#include "Rational.h"
#include "Matrix.hpp"
#include "GaussSolution.hpp"
#include "KramerSolution.hpp"


typedef std::vector<Rational> RationalVector;

void print(std::string str) {
    std::cout << str;
}

void printResult(RationalVector result, int n) {
    for (int i=0; i<n; i++) {
        std::cout << i << ". " << result[i] << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    
    return 0;
}


