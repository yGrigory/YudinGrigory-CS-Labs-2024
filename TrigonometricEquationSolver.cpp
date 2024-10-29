#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kmaxIterationsCount = 1e8 - 1;

struct MethodResult {
    double x;
    int iterationsCount;
    bool isRoot = true;
};

enum class MethodOptions {
    IterationMethod = 1,
    NewtonsMethod = 2,
    BisectionMethod = 3,
};

struct InputData {
    double epsilon;
    double coefficient;
};

void PrintResult(double x, int iterationsCount, int precision) {
    std::cout << std::endl << "Приближённое значение корня уравнения: " << std::fixed << std::setprecision(precision) << x << std::endl;
    std::cout << "Количество итераций: " << iterationsCount << std::endl << std::endl;
}

[[nodiscard]] double CalculateIterationMethodX(double coefficient, double x) {
    return coefficient * std::cos(x);
}

[[nodiscard]] double CalculateRoot(double x, double coefficient) {
    return (x - coefficient * std::cos(x));
}

[[nodiscard]] double CalculateDerivative(double (*calculatedFunction)(double, double), double x, double epsilon) {
    return (calculatedFunction(x + epsilon, epsilon) - calculatedFunction(x - epsilon, epsilon)) / (2 * epsilon);
}

InputData BasicDataEntry() {
    double epsilon{};
    double coefficient{};

    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;
    std::cout << "Введите коэффициент уравнения при cos(x): ";
    std::cin >> coefficient;

    InputData result = {epsilon, coefficient};

    return result;
}

}  // namespace

namespace TrigonometricEquationSolver {
enum class MethodOptions {
    IterationMethod = 1,
    NewtonsMethod = 2,
    BisectionMethod = 3,
};

[[nodiscard]] MethodResult CalculateIterationMethod(double epsilon, double coefficient) {
    double x = 0.0;
    int iterationsCount = 0;

    while (fabs(coefficient * std::cos(x) - x) >= epsilon && iterationsCount < kmaxIterationsCount) {
        x = CalculateIterationMethodX(coefficient, x);
        ++iterationsCount;
    }

    MethodResult result = {x, iterationsCount};

    if (iterationsCount == kmaxIterationsCount) {
        result.isRoot = false;
    }

    return result;
}

[[nodiscard]] MethodResult CalculateNewtonsMethod(double initialApproximation, double epsilon, double coefficient) {
    int iterationsCount = 0;
    double x = initialApproximation;
    double f{};
    double derivativeF{};

    while (fabs(CalculateRoot(x, coefficient)) >= epsilon && iterationsCount < kmaxIterationsCount) {
        f = CalculateRoot(x, coefficient);
        derivativeF = CalculateDerivative(CalculateRoot, x, coefficient);
        x = x - f / derivativeF;
        ++iterationsCount;
    }

    MethodResult result = {x, iterationsCount};

    if (iterationsCount == kmaxIterationsCount) {
        result.isRoot = false;
    }

    return result;
}

[[nodiscard]] MethodResult CalculateBisectionMethod(double leftBoundary, double rightBoundary, double epsilon, double coefficient) {
    int iterationsCount = 0;
    double middleValue = 0.0;
    double calculatedMiddleValue = 0.0;
    double calculatedRightBoundary = 0.0;

    if (leftBoundary > rightBoundary) {
        return {middleValue, iterationsCount, false};
    }

    while (fabs(rightBoundary - leftBoundary) > epsilon && iterationsCount < kmaxIterationsCount) {
        calculatedRightBoundary = CalculateRoot(rightBoundary, coefficient);
        middleValue = (leftBoundary + rightBoundary) / 2;
        calculatedMiddleValue = CalculateRoot(middleValue, coefficient);

        if (calculatedMiddleValue < 0 && calculatedRightBoundary > 0) {
            leftBoundary = middleValue;
        } else {
            rightBoundary = middleValue;
        }
        ++iterationsCount;
    }

    MethodResult result = {middleValue, iterationsCount};

    if (iterationsCount == kmaxIterationsCount) {
        result.isRoot = false;
    }

    return result;
}
void RunNewtonsMethod() {
    double initialApproximation = {};

    InputData result = BasicDataEntry();

    std::cout << "Введите начальное приближение для поиска корня уравнения: ";
    std::cin >> initialApproximation;

    MethodResult NewtonsMethodResult = TrigonometricEquationSolver::CalculateNewtonsMethod(initialApproximation, result.epsilon, result.coefficient);

    if (!NewtonsMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой коэффициент перед cos(x) или другое начальное приближение: " << std::endl;
    } else {
        PrintResult(NewtonsMethodResult.x, NewtonsMethodResult.iterationsCount, static_cast<int>(fabs(log10(result.epsilon))));
    }
}

void RunBisectionMethod() {
    double leftBoundary{};
    double rightBoundary{};

    InputData result = BasicDataEntry();

    std::cout << "Введите начало диапазона: ";
    std::cin >> leftBoundary;
    std::cout << "Введите конец диапазона: ";
    std::cin >> rightBoundary;

    MethodResult BisectionMethodResult =
        TrigonometricEquationSolver::CalculateBisectionMethod(leftBoundary, rightBoundary, result.epsilon, result.coefficient);

    if (!BisectionMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой диапазон, погрешность или коэффициент при cos(x)" << std::endl;
    } else {
        PrintResult(BisectionMethodResult.x, BisectionMethodResult.iterationsCount, static_cast<int>(fabs(log10(result.epsilon))));
    }
}
void RunIterationMethod() {
    InputData result = BasicDataEntry();

    MethodResult IterationMethodResult = TrigonometricEquationSolver::CalculateIterationMethod(result.epsilon, result.coefficient);

    if (!IterationMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой коэффициент при cos(x) или другую погрешность" << std::endl;
    } else {
        PrintResult(IterationMethodResult.x, IterationMethodResult.iterationsCount, static_cast<int>(fabs(log10(result.epsilon))));
    }
}

void PrintMenu() {
    std::cout << "1 - Решение уравнения методом итерации" << std::endl;
    std::cout << "2 - Решение уравнения методом Ньютона" << std::endl;
    std::cout << "3 - Решение уравнения методом половинного деления" << std::endl << std::endl;
    std::cout << "Введите номер задачи: ";
}

void StartApp() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        PrintMenu();

        int task{};
        std::cin >> task;

        switch (static_cast<MethodOptions>(task)) {
            case MethodOptions::IterationMethod:
                RunIterationMethod();
                break;
            case MethodOptions::NewtonsMethod:
                RunNewtonsMethod();
                break;
            case MethodOptions::BisectionMethod:
                RunBisectionMethod();
                break;
            default:
                std::cout << "Введён несуществующий номер задачи" << std::endl;
                break;
        }

        std::cout << "Хотите продолжить работу (y - продолжить, n - закончить): " << std::endl;
        std::cin >> continueExecution;
    }
}
}  // namespace TrigonometricEquationSolver
