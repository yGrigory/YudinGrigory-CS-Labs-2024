#include "sorting.hpp"
#include <iostream>
#include <random>

namespace {
const int kStaticArraySize = 5;

const int kMinArrayElement = 0;
const int kMaxArrayElement = 99;

const int kRangeStart = 0;

const int kminPermutationsCount = 0;

[[nodiscard]] int* GenerateArray(int* array, size_t arraySize) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinArrayElement, kMaxArrayElement);

    for (size_t i = kRangeStart; i < arraySize; ++i) {
        array[i] = distribution(randomEngine);
    }

    return array;
}

void PrintSourceArray(int* array, size_t arraySize) {
    std::cout << "Исходный массив: ";
    for (size_t i = kRangeStart; i < arraySize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void PrintSortingType(bool isSelectionSort) {
    std::cout << "-------------------------------------" << std::endl;
    if (isSelectionSort) {
        std::cout << "Сортировка выбором" << std::endl;
    } else {
        std::cout << "Пузырьковая сортировка" << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}

void PrintArray(int* array, size_t arraySize, bool isStaticArray, bool isAscending) {
    if (isStaticArray) {
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
        std::cout << array[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void PrintResult(Sorting::FunctionResult result) {
    std::cout << std::endl << "Количестов сравнений: " << result.comparisonsCount << std::endl;
    std::cout << "Количество перестановок: " << result.permutationsCount << std::endl;
}
}  // namespace

namespace Sorting {

[[nodiscard]] FunctionResult CalculateBubbleSort(int* array, bool isAscending, size_t arraySize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;

    for (size_t i = kRangeStart; i < arraySize - 1; ++i) {
        bool isSorted = true;
        for (size_t j = kRangeStart; j < arraySize - i - 1; ++j) {
            ++comparisonsCount;
            if ((isAscending && array[j + 1] < array[j]) || (!isAscending && array[j + 1] > array[j])) {
                std::swap(array[j], array[j + 1]);
                ++permutationsCount;
                isSorted = false;
            }
        }
        if (isSorted) {
            break;
        }
    }
    FunctionResult result = FunctionResult{permutationsCount, comparisonsCount};
    return result;
}

[[nodiscard]] FunctionResult CalculateSelectionSort(int* array, bool isAscending, size_t arraySize) {
    int comparisonsCount = 0;
    int permutationsCount = 0;

    for (size_t i = kRangeStart; i < arraySize - 1; ++i) {
        size_t elementIndex = i;
        if (isAscending) {
            for (size_t j = i + 1; j < arraySize; ++j) {
                ++comparisonsCount;
                if (array[j] < array[elementIndex]) {
                    elementIndex = j;
                    ++permutationsCount;
                }
            }
            std::swap(array[i], array[elementIndex]);
        } else {
            for (size_t j = i + 1; j < arraySize; ++j) {
                ++comparisonsCount;
                if (array[j] > array[elementIndex]) {
                    elementIndex = j;
                    ++permutationsCount;
                }
            }
            std::swap(array[i], array[elementIndex]);
        }
    }
    FunctionResult result = FunctionResult{permutationsCount, comparisonsCount};
    return result;
}

void RunOutputFunction(int* array, size_t arraySize, bool isAscending) {
    FunctionResult sortingResult = CalculateSelectionSort(array, isAscending, arraySize);
    PrintResult(sortingResult);
}

void RunStaticArraySort(int* array) {
    PrintSourceArray(array, kStaticArraySize);
    PrintSortingType(true);

    int selectionSortArray[kStaticArraySize];
    int bubbleSortArray[kStaticArraySize];
    std::copy(array, array + kStaticArraySize, selectionSortArray);
    std::copy(array, array + kStaticArraySize, bubbleSortArray);

    RunOutputFunction(selectionSortArray, kStaticArraySize, true);
    PrintArray(selectionSortArray, kStaticArraySize, true, true);

    RunOutputFunction(selectionSortArray, kStaticArraySize, true);
    PrintArray(selectionSortArray, kStaticArraySize, true, true);

    RunOutputFunction(selectionSortArray, kStaticArraySize, false);
    PrintArray(selectionSortArray, kStaticArraySize, true, false);

    PrintSortingType(false);

    RunOutputFunction(bubbleSortArray, kStaticArraySize, true);
    PrintArray(bubbleSortArray, kStaticArraySize, true, true);

    RunOutputFunction(bubbleSortArray, kStaticArraySize, true);
    PrintArray(bubbleSortArray, kStaticArraySize, true, true);

    RunOutputFunction(bubbleSortArray, kStaticArraySize, false);
    PrintArray(bubbleSortArray, kStaticArraySize, true, false);
}

void RunDynamicArraySort(int* array, size_t arraySize) {
    PrintSortingType(true);
    PrintSourceArray(array, arraySize);

    int* selectionSortArray = new int[arraySize];
    int* bubbleSortArray = new int[arraySize];
    std::copy(array, array + arraySize, selectionSortArray);
    std::copy(array, array + arraySize, bubbleSortArray);

    RunOutputFunction(selectionSortArray, arraySize, true);
    RunOutputFunction(selectionSortArray, arraySize, true);
    RunOutputFunction(selectionSortArray, arraySize, false);

    delete[] selectionSortArray;

    PrintSortingType(true);

    RunOutputFunction(bubbleSortArray, arraySize, true);
    RunOutputFunction(bubbleSortArray, arraySize, true);
    RunOutputFunction(bubbleSortArray, arraySize, false);

    delete[] bubbleSortArray;
}

void SelectTask() {
    int task{};
    std::cin >> task;

    int staticArray[kStaticArraySize]{};
    int* dynamicArray = nullptr;
    int dynamicArraySize{};

    switch (static_cast<ArrayType>(task)) {
        case ArrayType::StaticArray:
            RunStaticArraySort(GenerateArray(staticArray, kStaticArraySize));
            break;
        case ArrayType::DynamicArray:
            std::cout << "Введите размер для динамического массива: ";
            std::cin >> dynamicArraySize;

            dynamicArray = new int[dynamicArraySize];
            RunDynamicArraySort(GenerateArray(dynamicArray, dynamicArraySize), dynamicArraySize);

            delete[] dynamicArray;
            break;
        default:
            std::cout << "Введён неверный номер задачи" << std::endl;
            break;
    }
}

void StartApp() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        std::cout << "1 - Сортировка статического массива" << std::endl;
        std::cout << "2 - Сортировка динамического массива" << std::endl;
        std::cout << "Введите (1 или 2): ";

        SelectTask();

        std::cout << "Хотите продолжить работу (y - продолжить, n - закончить): ";
        std::cin >> continueExecution;
    }
}
}  // namespace Sorting
