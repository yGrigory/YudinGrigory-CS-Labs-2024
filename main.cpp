#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTask1 = 1;
const int kTask2 = 2;
const int kTask3 = 3;
const int kTask4 = 4;
const int kFixedWidth = 12;
const int kFixedPrecision = 8;
}  // namespace

void Task1() {
    int n = {};
    int m = {};
    int numsSum = 0;
    const int divider = 5;
    const int rangeStart = 1;

    std::cout << "Введите натуральные чила n, m, притом m < n: ";
    std::cin >> n >> m;

    for (int numsIterator = rangeStart; numsIterator <= n; ++numsIterator) {
        if (numsIterator % divider == 0 && numsIterator % m != 0) {
            numsSum += numsIterator;
        }
    }

    std::cout << numsSum << std::endl;
}

void Task2() {
    const int rangePozitiveAStart = 2;
    const int rangeNegativeAStart = 3;
    const int rangePozitiveAEnd = 8;
    const int rangeNegativeAEnd = 9;
    double a = {};
    double numsProduct = 1;

    std::cout << "Введите число a: ";
    std::cin >> a;

    if (a >= 0) {
        for (int numsIterator = rangePozitiveAStart; numsIterator <= rangePozitiveAEnd; numsIterator += 2) {
            numsProduct *= pow(numsIterator, 2);
        }
        numsProduct -= a;
    } else {
        for (int numsIterator = rangeNegativeAStart; numsIterator <= rangeNegativeAEnd; numsIterator += 3) {
            numsProduct *= (numsIterator - 2);
        }
    }

    std::cout << numsProduct << std::endl;
}

void CalculateTaylorRow(double x) {
    const double delta = 1e-6;
    double y = log((1 + x) / (1 - x));
    int n = 1;
    double s = x;
    double prevElem = x;
    double curElem = x;

    while (2 * curElem > delta) {
        double k = pow(x, 2) * (2 * n - 1) / (2 * n + 1);
        curElem = prevElem * k;
        prevElem = curElem;
        s += curElem;
        n++;
    }

    std::cout << std::setw(kFixedWidth) << x << std::setw(kFixedWidth) << std::setprecision(kFixedPrecision) << y << std::setw(kFixedWidth)
              << std::setprecision(kFixedPrecision) << 2 * s << std::setw(kFixedWidth) << n << std::endl;
}

void Task3() {
    const double h = 0.2;
    const int rangeEnd = 1;
    double x = 0;

    std::cout << std::setw(kFixedWidth) << "x" << std::setw(kFixedWidth) << "Y" << std::setw(kFixedWidth) << "s" << std::setw(kFixedWidth) << "n"
              << std::endl;

    while (x < rangeEnd) {
        CalculateTaylorRow(x);
        x += h;
    }
}

void CalculateY(double n, double x) {
    const int n1 = 3;
    const int n2 = 5;
    const int n3 = 10;

    int rangeStart = 1;
    double y = x;

    for (int numsIterator = rangeStart; numsIterator <= n; numsIterator++) {
        y += (pow(x, numsIterator + 1)) / (numsIterator * pow(2, numsIterator));
        if ((numsIterator == n1) || (numsIterator == n2) || (numsIterator == n3) ||
            (numsIterator == n && numsIterator != n1 && numsIterator != n2 && numsIterator != 3)) {
            std::cout << "Для n = " << numsIterator << ", Y = " << y << std::endl;
        }
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

    int rangeStart = 1;
    double y = x;
    for (int numsIterator = rangeStart; numsIterator <= n; numsIterator++) {
        y += (pow(x, numsIterator + 1)) / (numsIterator * pow(2, numsIterator));
        if ((numsIterator == n1) || (numsIterator == n2) || (numsIterator == n3) ||
            (numsIterator == n && numsIterator != n1 && numsIterator != n2 && numsIterator != n3)) {
            std::cout << "Для n = " << numsIterator << ", Y = " << y << std::endl;
        }
    }
}

int main() {
    char workStatus = 'y';
    while (workStatus == 'y') {
        int userChoice{};
        std::cout << "Введите номер задачи от 1 до 4: ";
        std::cin >> userChoice;
        switch (userChoice) {
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
        std::cin >> workStatus;
    }
}
