#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Функция для вычисления значения функции
double function(double x) {
    if (x == 0) {
        return 0;
    }
    if (x < 0) {
        return -0.5 * x; // Линия слева
    }
    if (x > 0 && x < 2) {
        return  -sqrt(4 - x * x) + 2; // Нижняя правая часть полукруга
    }
    if (x >= 2 && x <= 4) {
        return sqrt(4 - (x - 2) * (x - 2)); // Верхняя правая часть полукруга
    }
    if (x > 4) {
        return -0.5 * x + 2; // Линия справа
    }
}

// Функция округления до 0.001
double roundToThousandth(double value) {
    return round(value * 1000) / 1000;
}

int main() {
    setlocale(LC_ALL, "ru");
    double beg, end, dx;
    cout << "Введите Xнач: ";
    cin >> beg;
    cout << "Введите Xкон: ";
    cin >> end;
    cout << "Введите шаг dx: ";
    cin >> dx;

    // Заголовок таблицы
    cout << "Значения функции на заданном интервале:" << endl << endl;
    cout << setw(6) << "X" << " | " << setw(0) << "Y" << endl;
    cout << "-------|-------" << endl;

    for (double x = beg; x <= end; x += dx) {
        double y = function(x);
        y = roundToThousandth(y);
        cout << setw(6) << x << " | " << setw(0) << y << endl;
    }

    return 0;
}
