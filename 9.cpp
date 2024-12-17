#include <iostream>
#include <string>
using namespace std;

void printIsoscelesTriangle(int n) {
    int maxWidth = 2 * n - 1; // Максимальная ширина треугольника

    for (int i = 0; i < n; ++i) {
        int stars = 2 * i + 1; // Количество символов * в текущей строке
        int spaces = (maxWidth - stars) / 2; // Количество пробелов перед символами *

        // Выводим пробелы
        for (int j = 0; j < spaces; ++j) {
            cout << ' ';
        }

        // Выводим символы *
        for (int j = 0; j < stars; ++j) {
            cout << '*';
        }

        cout << endl;
    }
}

int main() {
    int N;
    cout << "Введите количество треугольников: ";
    cin >> N;

    for (int i = 0; i < N; ++i) {
        printIsoscelesTriangle(N);
        cout << endl; // Пустая строка между треугольниками
    }

    return 0;
}
