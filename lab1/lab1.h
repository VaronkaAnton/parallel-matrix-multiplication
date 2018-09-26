#ifndef LAB1_LAB1_H
#define LAB1_LAB1_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "omp.h"
#include "utils.h"

using namespace std;

void point_multiplication(matrix_t&, matrix_t&, matrix_t&, int);

void block_multiplication(matrix_t&, matrix_t&, matrix_t&, int, int);

#endif //LAB1_LAB1_H
