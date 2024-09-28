#include <iostream>

int findingSum() {
    int n;
    int m;
    int numsSum = 0;
    int divider = 5;

    std::cout << "Введите числа n и m, m < n" << std::endl;
    std::cin >> n >> m;

    for (int i = 0; i < n + 1; ++i) {
        if (i % 5 == 0 && i % m != 0) {
            numsSum += i;
        }
    }
    return numsSum;
}

int findingPr() {
    int a;
    int pr = 1;

    std::cout << "Введите число a" << std::endl;
    std::cin >> a;

    if (a >= 0) {
        for (int i = 2; i <= 8; ++i) {
            pr *= (i * i - a);
        }
    } else {
        for (int i = 3; i <= 9; ++i) {
            pr *= (i - 2);
        }
    }
    return pr;
}

int main() {
    std::cout << findingPr();
}
