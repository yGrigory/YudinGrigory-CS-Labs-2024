#include "MatPrinter.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <random>

namespace {
const int kStaticMatrixSize = 10;

double** GetPointerArray(double (*matrix)[kStaticMatrixSize]) {
    double** pointerArray = new double*[kStaticMatrixSize];

    for (int i = 0; i < kStaticMatrixSize; i++) {
        pointerArray[i] = matrix[i];
    }

    return pointerArray;
}

void RunTask(int n, int m, int precision, bool scientific) {
    Matrix::Matrix dynamicMatrix = Matrix::CreateDynamicMatrix(n, m);
    Matrix::FillMatrix(dynamicMatrix);

    if (scientific) {
        std::cout << std::endl << "Матрица A в эспоненциальном формате" << std::endl;
        Matrix::PrintMatrix(dynamicMatrix, precision, true);
    } else {
        std::cout << std::endl << "Матрица A с точностью " << precision << std::endl;
        Matrix::PrintMatrix(dynamicMatrix, precision);
    }

    Matrix::DeleteMatrix(dynamicMatrix);

    double matrixB[kStaticMatrixSize][kStaticMatrixSize];

    const int base10 = 10;
    for (int i = 0; i < kStaticMatrixSize; i++) {
        for (int j = 0; j < kStaticMatrixSize; j++) {
            matrixB[i][j] = i * base10 + j + 1;
        }
    }

    std::cout << matrixB << std::endl;
    std::cout << matrixB[1] << "\t" << *matrixB+2 << std::endl;
    std::cout << matrixB[2][3] << '\t' << *(matrixB+2) << "\t" << *(matrixB+3) + 6 << std::endl;
    std::cout << *(*(matrixB + 3) - 1) << '\t' << *matrixB[2] - 10 << std::endl;
    std::cout << --*(matrixB[4] - 6) << '\t' << ++*(*matrixB + 4) << std::endl;
    std::cout << matrixB[1] + 4 << '\t' << *(matrixB + 3)[2] << '\t' << *matrixB[2] - 1 << std::endl;

    double** pointerArray = GetPointerArray(matrixB);

    std::cout << std::endl << "Матрица B" << std::endl;
    Matrix::PrintMatrix(Matrix::Matrix{pointerArray, kStaticMatrixSize, kStaticMatrixSize}, 0);

    delete[] pointerArray;
}
}  // namespace

namespace AppLogic {
void StartApp() {
    int n{};
    int m{};
    int precision{};
    char scientific{};

    while (true) {
        std::cout << "N = ";
        std::cin >> n;
        std::cout << "M = ";
        std::cin >> m;
        std::cout << "precision = ";
        std::cin >> precision;
        std::cout << "scientific (y/n) = ";
        std::cin >> scientific;

        RunTask(n, m, precision, scientific == 'y');
    }
}
}  // namespace AppLogic
