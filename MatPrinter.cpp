#include "MatPrinter.hpp"

#include <iomanip>
#include <iostream>

namespace {
const int kMaxWidth = 120;
const int kFixedSpace = 8;
const int kScientificSpace = 12;

void PrintMatrixPart(const Matrix::Matrix& matrix, int start, int amount, int precision, bool scientific) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = start; j < std::min(matrix.m, start + amount); j++) {
            if (scientific) {
                std::cout << std::setw(precision + kScientificSpace) << std::setprecision(precision) << std::scientific << matrix.array[i][j];
            } else {
                std::cout << std::setw(precision + kFixedSpace) << std::fixed << std::setprecision(precision) << matrix.array[i][j];
            }
        }

        std::cout << std::endl;
    }
}

void PrintFrameLine(char chr) {
    for (int i = 0; i < kMaxWidth; i++) {
        std::cout << chr;
    }
    std::cout << std::endl;
}
}  // namespace

namespace Matrix {
void PrintMatrix(const Matrix& matrix, int precision, bool scientific) {
    int cellWidth{};
    if (scientific) {
        cellWidth = precision + kScientificSpace;
    } else {
        cellWidth = precision + kFixedSpace;
    }
    const int amount = kMaxWidth / cellWidth;

    PrintFrameLine('=');

    for (int part = 0; part < (matrix.m + amount - 1) / amount; part++) {
        PrintMatrixPart(matrix, part * amount, amount, precision, scientific);

        if (part != (matrix.m + amount - 1) / amount - 1) {
            PrintFrameLine('-');
        }
    }

    PrintFrameLine('=');
}
}  // namespace Matrix
