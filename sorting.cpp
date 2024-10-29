#include <iostream>
#include <random>

namespace {
const int kStaticArrSize = 10;
const int kMinArrElement = 0;
const int kMaxArrElement = 99;
const int kRangeStart = 0;
}  // namespace

namespace Sorting {
enum class ArrayOptions {
    SelectionSort = 1,
    BubbleSort = 2,
};
struct FunctionResult {
    int* arr;
    int permutationsCount;
    int comparisonsCount;
};
void PrintResult(FunctionResult result, size_t arrSize) {
    std::cout << "Количестов сравнений: " << result.comparisonsCount << std::endl;
    std::cout << "Количество перестановок: " << result.permutationsCount << std::endl << std::endl;
}

void PrintMenu() {
    std::cout << "1 - Сортировка статического массива" << std::endl;
    std::cout << "2 - Сортировка динамического массива" << std::endl;
}

[[nodiscard]] FunctionResult CalculateSelectionSort(int* arr, size_t arrSize = kStaticArrSize) {
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
    FunctionResult result = {arr, permutationsCount, comparisonsCount};
    return result;
}

[[nodiscard]] FunctionResult CalculateBubbleSort(int* arr, size_t arrSize = kStaticArrSize) {
    //
    return FunctionResult{};
}

[[nodiscard]] int* GenerateArray(size_t arrSize = kStaticArrSize) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinArrElement, kMaxArrElement);
    int* array = new int[arrSize];
    for (int i = kRangeStart; i < arrSize; ++i) {
        array[i] = distribution(randomEngine);
    }

    return array;
}

void StartApp() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        PrintMenu();

        int task{};
        std::cin >> task;

        int* staticArray = GenerateArray();
        switch (static_cast<ArrayOptions>(task)) {
            case ArrayOptions::SelectionSort:
                CalculateSelectionSort(staticArray);
                break;
            case ArrayOptions::BubbleSort:
                CalculateBubbleSort(staticArray);
                break;
            default:
                break;
        }
    }
}
}  // namespace Sorting
