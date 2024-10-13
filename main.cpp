#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTask1 = 1;
const int kTask2 = 2;
const int kTask3 = 3;
const int kTask4 = 4;

const int kTask3WidthX = 12;
const int kTask3WidthY = 12;
const int kTask3WidthS = 12;
const int kTask3WidthN = 4;

const int kTask3PrecisionX = 1;
const int kTask3PrecisionY = 8;
const int kTask3PrecisionS = 8;
const int kTask3PrecisionN = 0;
}  // namespace

void Task1() {
    int n = {};
    int m = {};

    std::cout << "Введите натуральные чила n, m, притом m < n: ";
    std::cin >> n >> m;

    if (m >= n || n < 1 || m < 1) {
        std::cout << "Некорректный ввод" << std::endl;
        return;
    }

    const int step = 5;
    const int rangeStart = 5;
    int sum = 0;

    for (int i = rangeStart; i <= n; i += step) {
        if (i % m != 0) {
            sum += i;
        }
    }

    std::cout << "Сумма: " << sum << std::endl;
}

void Task2() {
    const int rangeNotNegativeAStart = 2;
    const int rangeNotNegativeAEnd = 8;
    const int rangeNegativeAStart = 3;
    const int rangeNegativeAEnd = 9;

    double a = {};

    std::cout << "Введите число a: ";
    std::cin >> a;

    double product = 1.0;
    if (a >= 0) {
        for (int i = rangeNotNegativeAStart; i <= rangeNotNegativeAEnd; i += 2) {
            product *= (i * i) - a;
        }
        product -= a;
    } else {
        for (int i = rangeNegativeAStart; i <= rangeNegativeAEnd; i += 3) {
            product *= (i - 2);
        }
    }

    std::cout << "Произведение: " << product << std::endl;
}

void CalculateTaylorSeries(double x) {
    const double epsilon = 1e-6;
    double y = std::log((1 + x) / (1 - x));
    int n = 1;
    double s = 2 * x;
    double prevSeriesElem = 2 * x;

    while (prevSeriesElem > epsilon) {
        double k = x * x * (2 * n - 1) / (2 * n + 1);
        prevSeriesElem *= k;
        s += prevSeriesElem;
        ++n;
    }

    std::cout << std::setw(kTask3WidthX) << std::fixed << std::setprecision(kTask3PrecisionX) << x << std::setw(kTask3WidthY)
              << std::setprecision(kTask3PrecisionY) << y << std::setw(kTask3WidthS) << std::setprecision(kTask3PrecisionS) << s
              << std::setw(kTask3WidthN) << n << std::endl;
}

void Task3() {
    const double h = 0.2;
    const double maxH = 0.8;
    double x = 0;

    std::cout << std::setw(kTask3WidthX) << "x" << std::setw(kTask3WidthY) << "Y" << std::setw(kTask3WidthS) << "s" << std::setw(kTask3WidthN) << "n"
              << std::endl;

    while (x <= maxH) {
        CalculateTaylorSeries(x);
        x += h;
    }
}

void Task4() {
    double n{};
    double x{};

    std::cout << "Введите натуральные значения n, x: ";
    std::cin >> n >> x;

    const int n1 = 3;
    const int n2 = 5;
    const int n3 = 10;
    const int rangeStart = 1;
    double y = x;

    for (int i = rangeStart; i <= n; ++i) {
        y += (pow(x, i + 1)) / (i * pow(2, i));
        if (i == n1 || i == n2 || i == n3 || i == n) {
            std::cout << "Для n = " << i << ", Y = " << y << std::endl;
        }
    }
}

int main(int, char**) {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        std::cout << "Задача 1 - поиск суммы на отрезке" << std::endl;
        std::cout << "Задача 2 - вычисление произведения чисел на отрезке" << std::endl;
        std::cout << "Задача 3 - вычисление ряда Тейлора" << std::endl;
        std::cout << "Задача 4 - вычисление Y по формуле" << std::endl;
        std::cout << "Введите номер задачи от 1 до 4: ";

        int task{};
        std::cin >> task;
        switch (task) {
            case 1:
                Task1();
                break;
            case 2:
                Task2();
                break;
            case 3:
                Task3();
                break;
            case 4:
                Task4();
                break;
            default:
                std::cout << "Введён несуществующий номер задачи" << std::endl;
        }

        std::cout << "Хотите продолжить работу (y - продолжить, n - завершить)? ";
        std::cin >> continueExecution;
    }
}
