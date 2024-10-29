#include <iostream>

const int kStaticArrSize = 10;
const int kMinArrElement = 0;
const int kMaxArrElement = 99;
const int kRangeStart = 0;

namespace Sorting {
enum class ArrayOptions {
    SelectionSort = 1,
    BubbleSort = 2
};
struct FunctionResult {
    int* arr;
    int permutationsCount;
    int comparisonsCount;
};

[[nodiscard]] FunctionResult CalculateSelectionSort(int* arr, size_t arrSize = kStaticArrSize);
[[nodiscard]] FunctionResult CalculateBubbleSort(int* arr, size_t arrSize = kStaticArrSize);

[[nodiscard]] int* GenerateArray(size_t arrSize = kStaticArrSize);

void PrintResult(FunctionResult result, size_t arrSize);

void StartApp();
void RunSelectionSort();
void RunBubbleSort();
}  // namespace Sorting
