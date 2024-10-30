#include <iostream>

const int kStaticArraySize = 10;
const int kMinArrElement = 0;
const int kMaxArrElement = 99;
const int kRangeStart = 0;
const int kminPermutationsCount = 0;

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

[[nodiscard]] FunctionResult CalculateAscendingSelectionSort(int* array, size_t arraySize = kStaticArraySize);
[[nodiscard]] FunctionResult CalculateAscendingBubbleSort(int* array, size_t arraySize = kStaticArraySize);

[[nodiscard]] int* GenerateArray(size_t arraySize = kStaticArraySize);

void PrintResult(FunctionResult result, size_t arraySize);

void StartApp();
void RunSelectionSort();
void RunBubbleSort();
}  // namespace Sorting
