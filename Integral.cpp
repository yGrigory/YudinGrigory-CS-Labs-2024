#include "Integral.hpp"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace {
const int kDecimalBase = 10;
const int kMaxFiguriesNumber = 1e9;
const int kFunctionsNumber = 4;

[[nodiscard]] double FunctionX(double x) {
    return x;
}

[[nodiscard]] double FunctionSin(double x) {
    const int k = 22;
    return std::sin(k * x);
}

[[nodiscard]] double FunctionXPow4(double x) {
    const int exp = 4;
    return std::pow(x, exp);
}

[[nodiscard]] double FunctionArctg(double x) {
    return std::atan(x);
}

[[nodiscard]] double CalcExactResultFunctionX(double& leftBoundary, double& rightBoundary) {
    double correctResult{};
    correctResult = (rightBoundary * rightBoundary - leftBoundary * leftBoundary) / 2;

    return correctResult;
}

[[nodiscard]] double CalcExactResultFunctionSin(double& leftBoundary, double& rightBoundary) {
    double correctResult{};
    const double k = 22.0;
    correctResult = (std::cos(leftBoundary * k) - std::cos(rightBoundary * k)) / k;

    return correctResult;
}

[[nodiscard]] double CalcExactResultFunctionXPow4(double& leftBoundary, double& rightBoundary) {
    const double exp = 5.0;
    double correctResult{};
    correctResult = (std::pow(rightBoundary, exp) - std::pow(leftBoundary, exp)) / exp;

    return correctResult;
}

[[nodiscard]] double CalcExactResultFunctionArctg(double& leftBoundary, double& rightBoudary) {
    double correctResult{};
    const double power = 2;
    correctResult = rightBoudary * std::atan(rightBoudary) - leftBoundary * std::atan(leftBoundary) -
                    (std::log(std::pow(rightBoudary, power) + 1) - std::log(std::pow(leftBoundary, power) + 1)) / power;

    return correctResult;
}

[[nodiscard]] double CalculateAccuracy(int precision) {
    return std::pow(kDecimalBase, -precision);
}

[[nodiscard]] int ReadPrecisionFromStdin() {
    int precision{};

    std::cout << "Введите точность вычисления (кол-во цифр после запятой): ";
    std::cin >> precision;
    return precision;
}
} // namespace

namespace TableStatistic {
void PrintTable(IntegralSolution::FunctionData functionData[], int functionsAmount, int precision) {
    const char sideSymbol = '|';
    const char horizontSymbol = '-';
    const char connectorSymbol = '+';

    const int columnAmount = 4;
    int columnWidth[columnAmount] = {18, 18, 18, 10};
    char* title[columnAmount] = {(char*)"    Функция     ", (char*)"  Точная сумма  ", (char*)"    Интеграл    ", (char*)" i  "};
    int size[columnAmount];
    for (int i = 0; i < columnAmount; i++) {
        size[i] = (int)std::strlen(title[i]);
    }

    std::cout << connectorSymbol << std::setfill(horizontSymbol);
    for (int j = 0; j < columnAmount - 1; j++)
        std::cout << std::setw(columnWidth[j]) << connectorSymbol;
    std::cout << std::setw(columnWidth[columnAmount - 1]) << connectorSymbol << std::endl;

    std::cout << sideSymbol;
    for (int j = 0; j < columnAmount; j++)
        std::cout << std::setw((columnWidth[j] - size[j]) / 2) << std::setfill(' ') << ' ' << title[j] << std::setw((columnWidth[j] - size[j]) / 2)
                 << sideSymbol;
    std::cout << std::endl;

    for (int i = 0; i < functionsAmount; i++) {
        std::cout << connectorSymbol << std::fixed;
        for (int j = 0; j < columnAmount - 1; j++)
            std::cout << std::setfill(horizontSymbol) << std::setw(columnWidth[j]) << connectorSymbol;
        std::cout << std::setw(columnWidth[columnAmount - 1]) << connectorSymbol << std::setfill(' ') << std::endl;

        std::cout << sideSymbol << std::setw((int)(columnWidth[0] - std::strlen(functionData[i].nameFunction)) / 2) << ' '
                 << functionData[i].nameFunction << std::setw((int)(columnWidth[0] - std::strlen(functionData[i].nameFunction)) / 2) << sideSymbol;
        std::cout << std::setw(columnWidth[1] - 1) << std::setprecision(precision) << functionData[i].exactValue << sideSymbol
                 << std::setw(columnWidth[2] - 1) << functionData[i].resultValue << sideSymbol << std::setw(columnWidth[3] - 1)
                 << functionData[i].iterationCount << sideSymbol << std::endl;
    }

    std::cout << connectorSymbol << std::setfill(horizontSymbol);
    for (int j = 0; j < columnAmount - 1; j++)
        std::cout << std::setw(columnWidth[j]) << connectorSymbol;
    std::cout << std::setw(columnWidth[columnAmount - 1]) << connectorSymbol << std::setfill(' ') << std::endl;
}
} // namespace TableStatistic

namespace IntegralSolution {
void CalculateRectangleIntegration(double (*function)(double), FunctionData& functionData, double& leftBoundary, double& rightBoundary, double accuracy) {
    int numberOfRectangles = 1;

    double delta = rightBoundary - leftBoundary;

    double firstSum{};
    firstSum *= delta;

    double secondSum = function(leftBoundary + delta / 2);

    while (std::abs(secondSum - firstSum) / 3 > accuracy && numberOfRectangles <= kMaxFiguriesNumber) {
        firstSum = 0;
        secondSum = 0;

        for (int i = 1; i <= numberOfRectangles; i++) {
            firstSum += function(leftBoundary + delta / 2 + (i - 1) * delta);
        }
        firstSum *= delta;

        delta /= 2;
        numberOfRectangles *= 2;

        for (int i = 1; i <= numberOfRectangles; i++) {
            secondSum += function(leftBoundary + delta / 2 + (i - 1) * delta);
        }
        secondSum *= delta;
    }

    functionData.resultValue = secondSum;
    functionData.iterationCount = numberOfRectangles;
}

void CalculateTrapezoidIntegration(double (*function)(double), FunctionData& functionData, double& leftBoundary, double& rightBoundary, double accuracy) {
    int numberOfTrapezoids = 1;

    double delta = rightBoundary - leftBoundary;
    double firstSum{};

    double secondSum = function(leftBoundary) + function(leftBoundary + delta);
    secondSum *= delta / 2;

    while (std::abs(secondSum - firstSum) / 3 > accuracy && numberOfTrapezoids <= kMaxFiguriesNumber) {
        firstSum = 0;
        secondSum = 0;

        for (int i = 1; i <= numberOfTrapezoids; i++) {
            firstSum += function(leftBoundary + (i - 1) * delta) + function(leftBoundary + i * delta);
        }
        firstSum *= delta / 2;

        delta /= 2;
        numberOfTrapezoids *= 2;

        for (int i = 1; i <= numberOfTrapezoids; i++) {
            secondSum += function(leftBoundary + (i - 1) * delta) + function(leftBoundary + i * delta);
        }
        secondSum *= delta / 2;
    }

    functionData.resultValue = secondSum;
    functionData.iterationCount = numberOfTrapezoids;
}

void RunIntegralSolution() {
    int precision = ReadPrecisionFromStdin();

    double accuracy = CalculateAccuracy(precision);

    double leftBoundary{};
    double rightBoundary{};

    std::cout << "Введите цифрами нижнюю и верхнюю границы интегрирования соответсвенно: \n";
    std::cout << "Нижняя - ";
    std::cin >> leftBoundary;
    std::cout << "Верхняя - ";
    std::cin >> rightBoundary;

    if (leftBoundary > rightBoundary) {
        std::cout << "Границы введены неверно\n";
        return;
    }

    double (*functions[kFunctionsNumber])(double) = {FunctionX, FunctionSin, FunctionXPow4, FunctionArctg};

    const char* functionsNames[kFunctionsNumber] = {"y=x ", "y=sin(22*x) ", "y=x^4 ", "y=arctg(x)"};

    double exactIntegralValues[kFunctionsNumber] = {
        CalcExactResultFunctionX(leftBoundary, rightBoundary), CalcExactResultFunctionSin(leftBoundary, rightBoundary),
        CalcExactResultFunctionXPow4(leftBoundary, rightBoundary), CalcExactResultFunctionArctg(leftBoundary, rightBoundary)};

    FunctionData functionsData[kFunctionsNumber]{};

    for (size_t i = 0; i < kFunctionsNumber; ++i) {
        size_t len = strlen(functionsNames[i]) + 1;
        functionsData[i].nameFunction = new char[len];
        strncpy(functionsData[i].nameFunction, functionsNames[i], len);

        functionsData[i].exactValue = exactIntegralValues[i];
        CalculateRectangleIntegration(functions[i], functionsData[i], leftBoundary, rightBoundary, accuracy);
    }

    std::cout << "\n\nРешение методом прямоугольников: \n";
    TableStatistic::PrintTable(functionsData, kFunctionsNumber, precision);

    for (size_t i = 0; i < kFunctionsNumber; ++i) {
        functionsData[i].exactValue = exactIntegralValues[i];
        CalculateTrapezoidIntegration(functions[i], functionsData[i], leftBoundary, rightBoundary, accuracy);
    }

    std::cout << "\n\nРешение методом трапеций: \n";
    TableStatistic::PrintTable(functionsData, kFunctionsNumber, precision);

    for (FunctionData element : functionsData) {
        delete element.nameFunction;
    }
}

void LaunchApp() {
    char continueExecution{'y'};

    while (continueExecution == 'y') {
        RunIntegralSolution();
        std::cout << "\n\nДля продолжения работы введите y, для выхода - любой другой символ: ";
        std::cin >> continueExecution;
    }
}
} // namespace IntegralSolution
