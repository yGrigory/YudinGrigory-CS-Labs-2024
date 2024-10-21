#include <cmath>
#include <iostream>

struct FunctionResult {
    double x;
    int iterationsCount;
};

namespace {
const int kmaxIterationsCount = 1e8 - 1;

void printResult(double x, int iterationsCount) {
    std::cout << std::endl << "Приближённое значение корня уравнения: " << x << std::endl;
    std::cout << "Количество итераций: " << iterationsCount << std::endl << std::endl;
}

[[nodiscard]] double CalculateIterationMethodX(double coefficient, double x) {
    return coefficient * cos(x);
}

[[nodiscard]] double CalculateNewtonsMethodResult(double x, double coefficient) {
    return (x - coefficient * cos(x));
}

[[nodiscard]] double CalculateNewtonsMethodDerivative(double (*calculatedFunction)(double, double), double x, double epsilon) {
    return (calculatedFunction(x + epsilon, epsilon) - calculatedFunction(x - epsilon, epsilon)) / (2 * epsilon);
}

[[nodiscard]] double CalculateFHalfCoefficientMethod(double value, double coefficient) {
    return value - coefficient * cos(value);
}
}  // namespace

namespace Calculation {
[[nodiscard]] FunctionResult CalculateIterationMethod(double epsilon, double coefficient) {
    double x = 0.0;
    int iterationsCount = 0;

    while (fabs(coefficient * cos(x) - x) >= epsilon && iterationsCount < kmaxIterationsCount) {
        x = CalculateIterationMethodX(coefficient, x);
        ++iterationsCount;
    }

    FunctionResult result = {x, iterationsCount};

    return result;
}

[[nodiscard]] FunctionResult CalculateNewtonsMethod(double initialApproximation, double epsilon, double coefficient) {
    int iterationsCount = 0;
    double x = initialApproximation;
    double f{};
    double derivativeF{};

    while (fabs(CalculateNewtonsMethodResult(x, coefficient)) >= epsilon && iterationsCount < kmaxIterationsCount) {
        f = CalculateNewtonsMethodResult(x, coefficient);
        derivativeF = CalculateNewtonsMethodDerivative(CalculateNewtonsMethodResult, x, coefficient);
        x = x - f / derivativeF;
        ++iterationsCount;
    }

    FunctionResult result = {x, iterationsCount};

    return result;
}

[[nodiscard]] FunctionResult CalculateHalfCoefficientMethod(double leftRangeLimit, double rightRangeLimit, double epsilon, double coefficient) {
    int iterationsCount = 0;
    double middleRangeValue = 0.0;
    double middleRangeFunctionValue = 0.0;
    double leftRangeFunctionValue = 0.0;
    double rightRangeFunctionValue = 0.0;

    while (fabs(rightRangeLimit - leftRangeLimit) > epsilon && iterationsCount < kmaxIterationsCount) {
        leftRangeFunctionValue = CalculateFHalfCoefficientMethod(leftRangeLimit, coefficient);
        rightRangeFunctionValue = CalculateFHalfCoefficientMethod(rightRangeLimit, coefficient);
        middleRangeValue = (leftRangeLimit + rightRangeLimit) / 2;
        middleRangeFunctionValue = CalculateFHalfCoefficientMethod(middleRangeValue, coefficient);

        if (middleRangeFunctionValue < 0 && rightRangeFunctionValue > 0) {
            leftRangeLimit = middleRangeValue;
        } else if (middleRangeFunctionValue > 0 && leftRangeFunctionValue < 0) {
            rightRangeLimit = middleRangeValue;
        }
        ++iterationsCount;
    }

    FunctionResult result = {middleRangeValue, iterationsCount};

    return result;
}
}  // namespace Calculation

namespace Run {
void RunNewtonsMethod() {
    int iterationsCount = 0;
    double epsilon = {};
    double coefficient = {};
    double initialApproximation = {};

    std::cout << "Введите начальное приближение для поиска корня уравнения: ";
    std::cin >> initialApproximation;
    std::cout << "Введите погрешность для нахождения корня: ";
    std::cin >> epsilon;
    std::cout << "Введите коэффициент уравнения при cos(x): ";
    std::cin >> coefficient;

    FunctionResult NewtonsMethodResult = Calculation::CalculateNewtonsMethod(initialApproximation, epsilon, coefficient);

    if (NewtonsMethodResult.iterationsCount == kmaxIterationsCount) {
        std::cout << std::endl << "Введите другой коэффициент перед cos(x) или другое начальное приближение: " << std::endl;
    } else {
        printResult(NewtonsMethodResult.x, NewtonsMethodResult.iterationsCount);
    }
}

void RunHalfCoefficientMethod() {
    double leftRangeLimit{};
    double rightRangeLimit{};
    double epsilon{};
    double coefficient{};

    std::cout << "Введите начало диапазона: ";
    std::cin >> leftRangeLimit;
    std::cout << "Введите конец диапазона: ";
    std::cin >> rightRangeLimit;
    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;
    std::cout << "Введите коэффициент уравнения при cos(x): ";
    std::cin >> coefficient;

    FunctionResult HalfCoefficientMethodResult = Calculation::CalculateHalfCoefficientMethod(leftRangeLimit, rightRangeLimit, epsilon, coefficient);

    if (HalfCoefficientMethodResult.iterationsCount == kmaxIterationsCount) {
        std::cout << std::endl << "Введите другой диапазон, погрешность или коэффициент при cos(x)" << std::endl;
    } else {
        printResult(HalfCoefficientMethodResult.x, HalfCoefficientMethodResult.iterationsCount);
    }
}
void RunIterationMethod() {
    double epsilon{};
    double coefficient{};

    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;
    std::cout << "Введите коэффициент уравнения при cos(x): ";
    std::cin >> coefficient;

    FunctionResult IterationMethodResult = Calculation::CalculateIterationMethod(epsilon, coefficient);

    if (IterationMethodResult.iterationsCount == kmaxIterationsCount) {
        std::cout << std::endl << "Введите другой коэффициент при cos(x) или другую погрешность" << std::endl;
    } else {
        printResult(IterationMethodResult.x, IterationMethodResult.iterationsCount);
    }
}
}  // namespace Run

namespace Menu {
enum class Option {
    Option1 = 1,
    Option2 = 2,
    Option3 = 3,
};

void inputProcessing(Option option) {
    switch (option) {
        case Option::Option1:
            Run::RunIterationMethod();
            break;
        case Option::Option2:
            Run::RunNewtonsMethod();
            break;
        case Option::Option3:
            Run::RunHalfCoefficientMethod();
            break;
        default:
            std::cout << "Введён несуществующий номер задачи" << std::endl;
            break;
    }
}

void start() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        std::cout << "1 - Решение уравнения методом итерации" << std::endl;
        std::cout << "2 - Решение уравнения методом Ньютона" << std::endl;
        std::cout << "3 - Решение уравнения методом половинного деления" << std::endl << std::endl;
        std::cout << "Введите номер задачи: ";

        int task{};
        std::cin >> task;

        inputProcessing(static_cast<Option>(task));

        std::cout << "Хотите продолжить работу (y - продолжить, n - закончить): " << std::endl;
        std::cin >> continueExecution;
    }
}
}  // namespace Menu
