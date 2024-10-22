#include <iostream>
#include "sorts.h"

int main(int, char**) {
    int* arr = Generate::GenerateArr();
    Result::PrintResult(arr, 10);
    int* sortedArr = Calculation::CalculateSelectionSort(arr, 10);
    Result::PrintResult(sortedArr, 10);

    delete[] arr;
}
