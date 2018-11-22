#include <iostream>
#include "matrix.h"
#include "Subspace_Iteration.h"
#include "ChafeInfante_equation.h"

#define SIZE 6

#include "math_vector.h"
#include "constructionW_row.h"



int main() {

    ChafeInfante_equation A;
    A.resize(10);
    A.solver();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}