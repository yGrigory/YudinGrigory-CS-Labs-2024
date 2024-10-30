#include <iostream>
#include <random>

namespace {
const int kStaticArraySize = 10;
const int kMinArrayElement = 0;
const int kMaxArrayElement = 99;
const int kRangeStart = 0;
const int kminPermutationsCount = 0;
}  // namespace

namespace Sorting {
enum class ArrayOptions {
    SelectionSort = 1,
    BubbleSort = 2,
};
struct FunctionResult {
    int* array;
    int permutationsCount;
    int comparisonsCount;
};

void PrintSourceArray(int* array, size_t arraySize) {
    std::cout << std::endl << "Исходный массив: ";
    for (size_t i = kRangeStart; i < arraySize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
void PrintResult(FunctionResult result, size_t arraySize, bool isStatic, bool isAscending) {
    if (isStatic) {
        std::cout << "Статический массив, отсортированный ";
    } else {
        std::cout << "Динамический массив, отсортированный ";
    }
    if (isAscending) {
        std::cout << "по возрастанию: ";
    } else {
        std::cout << "по убыванию: ";
    }
    for (size_t i = kRangeStart; i < arraySize; ++i) {
        std::cout << result.array[i] << " ";
    }
    std::cout << std::endl << "Количестов сравнений: " << result.comparisonsCount << std::endl;
    std::cout << "Количество перестановок: " << result.permutationsCount << std::endl << std::endl;
}

void PrintMenu() {
    std::cout << "1 - Сортировка выбором" << std::endl;
    std::cout << "2 - Пузырьковая сортировка" << std::endl;
    std::cout << "Введите (1 или 2): ";
}

[[nodiscard]] FunctionResult CalculateSelectionSortDiscending(int* array, size_t arraySize = kStaticArraySize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;

    for (size_t i = kRangeStart; i < arraySize; ++i) {
        for (size_t j = i + 1; j < arraySize; ++j) {
            ++comparisonsCount;
            if (array[j] > array[i]) {
                std::swap(array[i], array[j]);
                ++permutationsCount;
            }
        }
    }
    FunctionResult result = {array, permutationsCount, comparisonsCount};
    return result;
}

[[nodiscard]] FunctionResult CalculateBubbleSortDiscending(int* array, size_t arraySize = kStaticArraySize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;

    for (size_t i = kRangeStart; i < arraySize; ++i) {
        for (size_t j = i + 1; j < arraySize; ++j) {
            ++comparisonsCount;
            if (array[j] > array[i]) {
                std::swap(array[i], array[j]);
                ++permutationsCount;
            }
        }
    }
    FunctionResult result = {array, permutationsCount, comparisonsCount};
    return result;
}

[[nodiscard]] FunctionResult CalculateSelectionSortAcending(int* array, size_t arraySize = kStaticArraySize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;

    for (size_t i = kRangeStart; i < arraySize; ++i) {
        for (size_t j = i + 1; j < arraySize; ++j) {
            ++comparisonsCount;
            if (array[j] < array[i]) {
                std::swap(array[i], array[j]);
                ++permutationsCount;
            }
        }
    }
    FunctionResult result = {array, permutationsCount, comparisonsCount};
    return result;
}

[[nodiscard]] FunctionResult CalculateBubbleSortAcending(int* array, size_t arraySize = kStaticArraySize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;
    int permutationsPerPassCount = 0;

    for (size_t i = kRangeStart; i + 1 < arraySize; ++i) {
        permutationsPerPassCount = 0;
        for (size_t j = kRangeStart; j + 1 < arraySize - i; ++j) {
            ++comparisonsCount;
            if (array[j + 1] < array[j]) {
                std::swap(array[j], array[j + 1]);
                ++permutationsPerPassCount;
            }
        }
        if (permutationsPerPassCount == 0) {
            return FunctionResult{array, permutationsCount, comparisonsCount};
        }
        permutationsCount += permutationsPerPassCount;
    }
    return FunctionResult{array, permutationsCount, comparisonsCount};
}

[[nodiscard]] int* GenerateArray(size_t arraySize = kStaticArraySize) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinArrayElement, kMaxArrayElement);
    int* array = new int[arraySize];
    for (int i = kRangeStart; i < arraySize; ++i) {
        array[i] = distribution(randomEngine);
    }

    return array;
}

void RunSelectionSort(int* array, int arraySize, bool isStatic) {
    PrintSourceArray(array, arraySize);
    PrintResult(CalculateSelectionSortAcending(array), arraySize, isStatic, true);
    PrintResult(CalculateSelectionSortDiscending(array), arraySize, isStatic, false);
}

void RunBubbleSort(int* array, int arraySize, bool isStatic) {
    PrintSourceArray(array, arraySize);
    PrintResult(CalculateBubbleSortAcending(array), arraySize, isStatic, true);
    PrintResult(CalculateBubbleSortDiscending(array), arraySize, isStatic, false);
}

void StartApp() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        PrintMenu();

        int task{};
        std::cin >> task;

        std::cout << "Введите размер для динамического массива: ";
        int dynamicArraySize{};
        std::cin >> dynamicArraySize;

        int* staticArray = GenerateArray();
        int* dynamicArray = GenerateArray(dynamicArraySize);
        switch (static_cast<ArrayOptions>(task)) {
            case ArrayOptions::SelectionSort:
                RunSelectionSort(staticArray, kStaticArraySize, true);
                RunSelectionSort(dynamicArray, dynamicArraySize, false);
                break;
            case ArrayOptions::BubbleSort:
                RunBubbleSort(staticArray, kStaticArraySize, true);
                RunBubbleSort(dynamicArray, dynamicArraySize, false);
                break;
            default:
                break;
        }
        std::cout << "Хотите продолжить работу (y - продолжить, n - закончить): ";
        std::cin >> continueExecution;
    }
}
}  // namespace Sorting
