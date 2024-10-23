#include <iostream>
#include <random>

const int kStaticArrSize = 10;
const int kMinArrElement = 0;
const int kMaxArrElement = 99;
const int kRangeStart = 0;

namespace Result {
struct FunctionResult {
    int* arr;
    int permutationsCount;
    int comparisonsCount;
};
void PrintResult(FunctionResult result, size_t arrSize) {
    std::cout << "Количестов сравнений: " << result.comparisonsCount << std::endl;
    std::cout << "Количество перестановок: " << result.permutationsCount << std::endl << std::endl;
}

}  // namespace Result

namespace Calculation {
[[nodiscard]] Result::FunctionResult CalculateSelectionSort(int* arr, size_t arrSize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;

    for (int i = kRangeStart; i < arrSize; ++i) {
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[i]) {
                std::swap(arr[i], arr[j]);
                ++permutationsCount;
            }
            ++comparisonsCount;
        }
    }
    Result::FunctionResult result = {arr, permutationsCount, comparisonsCount};
    return result;
}
}  // namespace Calculation

namespace Generate {
[[nodiscard]] int* GenerateArr(size_t arrSize = kStaticArrSize) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinArrElement, kMaxArrElement);
    int* arr = new int[arrSize];
    for (int i = kRangeStart; i < arrSize; ++i) {
        arr[i] = distribution(randomEngine);
    }

    return arr;
}
}  // namespace Generate

namespace Run {
void start() {
    int* arr = Generate::GenerateArr();
}
}  // namespace Run
