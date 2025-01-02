#include "Integration.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const size_t kFunctionsNumber = 4;
const int kDecimalBase = 10;
const int kMaxIterationNumber = 1e9;

[[nodiscard]] Integration::IntegrationSegment ReadIntegrationSegmentFromStdin() {
    double lowerBoundary{};
    double upperBoundary{};

    std::cout << "Введите цифрами нижнюю и верхнюю границы интегрирования через пробел\n";
    std::cin >> lowerBoundary >> upperBoundary;

    return {.integrationLowerBoundary = lowerBoundary, .integrationUpperBoundary = upperBoundary};
}

[[nodiscard]] int ReadPrecisionValueFromStdin() {
    int precision{};
    std::cout << "Введите цифрами количество знаков после запятой (натуральное число), с точностью до которых будет вычислен корень уравнения\n";
    std::cin >> precision;

    return precision;
}

[[nodiscard]] double FirstFunction(double x) {
    return x;
}

[[nodiscard]] double SecondFunction(double x) {
    const double coefficient = 22;

    return std::sin(coefficient * x);
}

[[nodiscard]] double ThirdFunction(double x) {
    const double power = 4;

    return std::pow(x, power);
}

[[nodiscard]] double FourthFunction(double x) {
    return std::atan(x);
}

[[nodiscard]] double IntegrateFirstFunction(Integration::IntegrationSegment integrationSegment) {
    const double power = 2;

    return (std::pow(integrationSegment.integrationUpperBoundary, power) - std::pow(integrationSegment.integrationLowerBoundary, power)) / power;
}

[[nodiscard]] double IntegrateSecondFunction(Integration::IntegrationSegment integrationSegment) {
    const double coefficient = 22.;
    return (std::cos(integrationSegment.integrationLowerBoundary * coefficient) -
            std::cos(integrationSegment.integrationUpperBoundary * coefficient)) /
           coefficient;
}

[[nodiscard]] double IntegrateThirdFunction(Integration::IntegrationSegment integrationSegment) {
    const double power = 5;

    return (std::pow(integrationSegment.integrationUpperBoundary, power) - std::pow(integrationSegment.integrationLowerBoundary, power)) / power;
}

[[nodiscard]] double IntegrateFourthFunction(Integration::IntegrationSegment integrationSegment) {
    const double power = 2;

    return integrationSegment.integrationUpperBoundary * std::atan(integrationSegment.integrationUpperBoundary) -
           integrationSegment.integrationLowerBoundary * std::atan(integrationSegment.integrationLowerBoundary) -
           (std::log(std::pow(integrationSegment.integrationUpperBoundary, power) + 1) -
            std::log(std::pow(integrationSegment.integrationLowerBoundary, power) + 1)) /
               power;
}

void PrintTable(const Integration::Function* functionsData, const Integration::IntegrationSegment integrationSegment, const int precision) {
    const int twelveCharsWidth = 12;
    const int sixteenCharsWidth = 16;
    const int twentyThreeCharsWidth = 23;
    const int thirtyCharsWidth = 30;

    std::cout << "\nИнтегрирование с точностью " << std::pow(kDecimalBase, -precision) << " на отрезке от "
              << integrationSegment.integrationLowerBoundary << " до " << integrationSegment.integrationUpperBoundary << '\n';
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "|  Функция   |" << "    Интеграл    |" << " Cумма прямоугольников |" << " Итераций для прямоугольников |" << "    Cумма трапеций     |"  << "    Итераций для трапеций     |\n";
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < kFunctionsNumber; ++i) {
        std::cout << std::left << '|' << std::setw(twelveCharsWidth) << functionsData[i].name << '|' << std::setw(sixteenCharsWidth)
                  << std::setprecision(precision) << std::fixed << functionsData[i].preciseIntegralValue << '|';

        if (functionsData[i].rectangleIterationNumber >= kMaxIterationNumber) {
            std::cout << std::setw(twentyThreeCharsWidth) << std::setprecision(precision) << " не удалось вычислить  ";
        } else {
            std::cout << std::setw(twentyThreeCharsWidth) << std::setprecision(precision) << functionsData[i].rectangleIntegralSumValue;
        }
        std::cout << '|' << std::setw(thirtyCharsWidth) << functionsData[i].rectangleIterationNumber << "|";

        if (functionsData[i].trapezoidIterationNumber >= kMaxIterationNumber) {
            std::cout << std::setw(twentyThreeCharsWidth) << std::setprecision(precision) << " не удалось вычислить  ";
        } else {
            std::cout << std::setw(twentyThreeCharsWidth) << std::setprecision(precision) << functionsData[i].trapezoidIntegralSumValue;
        }
        std::cout << '|' << std::setw(thirtyCharsWidth) << functionsData[i].trapezoidIterationNumber << std::resetiosflags(std::ios::fixed) << "|\n";

    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
}
}  // namespace

namespace Integration {
void RectangleIntegration(Function& functionData, IntegrationSegment integrationSegment, double epsilon) {
    int iterationNumber = 1;

    double delta = integrationSegment.integrationUpperBoundary - integrationSegment.integrationLowerBoundary;

    double firstSum{};

    double secondSum = functionData.function(integrationSegment.integrationLowerBoundary + delta / 2);
    firstSum *= delta;

    while (std::abs(secondSum - firstSum) / 3 > epsilon & iterationNumber <= kMaxIterationNumber) {
        firstSum = 0;
        secondSum = 0;

        for (int i = 1; i <= iterationNumber; i++) {
            firstSum += functionData.function(integrationSegment.integrationLowerBoundary + delta / 2 + (i - 1) * delta);
        }
        firstSum *= delta;

        delta /= 2;
        iterationNumber *= 2;

        for (int i = 1; i <= iterationNumber; i++) {
            secondSum += functionData.function(integrationSegment.integrationLowerBoundary + delta / 2 + (i - 1) * delta);
        }
        secondSum *= delta;
    }

    functionData.rectangleIntegralSumValue = secondSum;
    functionData.rectangleIterationNumber = iterationNumber;
}

void TrapezoidIntegration(Function& functionData, IntegrationSegment integrationSegment, double epsilon) {
    int iterationNumber = 1;

    double delta = integrationSegment.integrationUpperBoundary - integrationSegment.integrationLowerBoundary;

    double firstSum{};

    double secondSum = functionData.function(integrationSegment.integrationLowerBoundary ) + functionData.function(integrationSegment.integrationLowerBoundary + delta);
    secondSum *= delta / 2;

    while (std::abs(secondSum - firstSum) / 3 > epsilon & iterationNumber <= kMaxIterationNumber) {
        firstSum = 0;
        secondSum = 0;

        for (int i = 1; i <= iterationNumber; i++) {
            firstSum += functionData.function(integrationSegment.integrationLowerBoundary + (i - 1) * delta) +
                        functionData.function(integrationSegment.integrationLowerBoundary + i * delta);
        }
        firstSum *= delta / 2;

        delta /= 2;
        iterationNumber *= 2;

        for (int i = 1; i <= iterationNumber; i++) {
            secondSum += functionData.function(integrationSegment.integrationLowerBoundary + (i - 1) * delta) +
                         functionData.function(integrationSegment.integrationLowerBoundary + i * delta);
        }
        secondSum *= delta / 2;
    }

    functionData.trapezoidIntegralSumValue = secondSum;
    functionData.trapezoidIterationNumber = iterationNumber;
}

void RunIntegration() {
    IntegrationSegment integrationSegment = ReadIntegrationSegmentFromStdin();

    if (integrationSegment.integrationLowerBoundary >= integrationSegment.integrationUpperBoundary) {
        std::cout << "Введен некорректный отрезок интегрирования";
        return;
    }

    int precision = ReadPrecisionValueFromStdin();
    double epsilon = std::pow(kDecimalBase, -precision);

    double (*functions[kFunctionsNumber])(double) = {FirstFunction, SecondFunction, ThirdFunction, FourthFunction};

    const char* functionsNames[kFunctionsNumber] = {"y=x", "y=sin(22*x)", "y=x^4", "y=arctg(x)"};

    double preciseIntegralValues[kFunctionsNumber] = {IntegrateFirstFunction(integrationSegment), IntegrateSecondFunction(integrationSegment),
                                                      IntegrateThirdFunction(integrationSegment), IntegrateFourthFunction(integrationSegment)};

    Function functionsData[kFunctionsNumber]{};

    for (size_t i = 0; i < kFunctionsNumber; ++i) {
        size_t len = strlen(functionsNames[i]) + 1;
        functionsData[i].name = new char [len];
        strncpy(functionsData[i].name, functionsNames[i], len);

        functionsData[i].preciseIntegralValue = preciseIntegralValues[i];
        functionsData[i].function = functions[i];
        RectangleIntegration(functionsData[i], integrationSegment, epsilon);
        TrapezoidIntegration(functionsData[i], integrationSegment, epsilon);
    }

    PrintTable(functionsData, integrationSegment, precision);

    for (Function element: functionsData) {
        delete element.name;
    }
}

void StartApp() {
    char continueExecution{'y'};

    while (continueExecution == 'y') {
        RunIntegration();
        std::cout << "Продолжить работу программы? Если да - введите y, если нет - введите любой другой символ" << '\n';
        std::cin >> continueExecution;
    }
}
}  // namespace Integration
