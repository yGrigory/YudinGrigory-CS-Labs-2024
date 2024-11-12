#include <iostream>

namespace Sorting {
const int kStaticArraySize = 10;

enum class ArrayType {
    StaticArray = 1,
    DynamicArray
};

struct FunctionResult {
    int permutationsCount;
    int comparisonsCount;
    bool isAscending;
    size_t arraySize;
};

[[nodiscard]] FunctionResult CalculateBubbleSort(int* array, bool isAscending, int arraySize);
[[nodiscard]] FunctionResult CalculateSelectionSort(int* array, bool isAscending, int arraySize);

void RunStaticArraySort();
void RunDynamicArraySort();

void SelectTask();
void StartApp();
}  // namespace Sorting
