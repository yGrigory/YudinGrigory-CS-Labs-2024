#include "Matrix.hpp"

#include <cmath>
#include <iostream>

namespace Matrix {
Matrix CreateDynamicMatrix(int n, int m) {
    Matrix matrix{new double*[n], n, m};
    for (int i = 0; i < n; i++) {
    matrix.array[i] = new double[m];
    }

    return matrix;
}

void FillMatrix(Matrix& matrix) {
    matrix.array[0][0] = 1;
    matrix.array[1][0] = 1;
    for (int i = 2; i < matrix.n; i++) {
    matrix.array[i][0] = -matrix.array[i - 1][0];
    }
    for (int j = 1; j < matrix.m; j++) {
    matrix.array[0][j] = matrix.array[0][j - 1] / (j + 1);
    }
    for (int i = 1; i < matrix.n; i++) {
    double fact = 1;
    for (int j = 1; j < matrix.m; j++) {
    fact *= j + 1;
    if (i < j) {
        matrix.array[i][j] = static_cast<double>(matrix.array[i - 1][j] / fact);
    } else if (i == j) {
        matrix.array[i][j] = 1.0;
    } else {
        matrix.array[i][j] = static_cast<double>(matrix.array[i][j - 1] / std::pow(j + 1, i + 1));
    }
    }
    }
}

void DeleteMatrix(Matrix& matrix) {
    delete[] matrix.array;
}
}  // namespace Matrix
