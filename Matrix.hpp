#pragma once

#include <cstddef>

namespace Matrix {
struct Matrix {
    double** array;
    int n, m;
};

Matrix CreateDynamicMatrix(int n, int m);
void FillMatrix(Matrix& matrix);
void DeleteMatrix(Matrix& matrix);
}  // namespace Matrix
