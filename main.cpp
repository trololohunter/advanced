#include <iostream>
#include "matrix.h"
#include "Subspace_Iteration.h"

#define SIZE 6

#include "math_vector.h"
#include "constructionW_row.h"


int main() {

    Subspace_Iteration A;
    A.resize(5,5);
    A.initial_value();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}