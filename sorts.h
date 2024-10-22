enum class Option {
    Option1 = 1,
    Option2 = 2
};

namespace Run {
void RunSelectionSort();
void RunBubbleSort();
}  // namespace Run

namespace Calculation {
int* CalculateSelectionSort(int* arr, size_t arrSize);
}

const int kStaticArrSize = 10;

namespace Generate {
[[nodiscard]] int* GenerateArr(size_t arrSize = kStaticArrSize);
}
namespace Result {
struct FunctionResult {
    int* arr;
    int permutationsCount;
    int comparisonsCount;
};

void PrintResult(int* arr, size_t arrSize);
}  // namespace Result
