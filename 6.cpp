#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 0, k = 1;
    std::cout << "Введите число N: ";
    cin >> n;
    int m = n - 1;
    int random[n][n];
    int randoms[n][n];
    int start = 0;
    int end = 9;

    for (int i = 0; i < n; i++)
    { // заполнение рандомными цифрами
        for (int j = 0; j < n; j++)
        {
            random[i][j] = rand() % (end - start + 1) + start;
        }
    }
    for (int i = 0; i < n; i++)
    { // вывод массива х1
        for (int j = 0; j < n; j++)
        {
            cout << random[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < n; i++) { // меняю столбцы
        int m = n - 1, k = 1, l = 0;
        bool flag = true;
        for (int j = 0; j < n; j++) {
            if (flag) {
                randoms[i][j] = random[i][l];
                l += 1;
                flag = false;
            }
            else {
                randoms[i][j] = random[i][m];
                m = m - 1;
                flag = true;
            }
        }
    }
    cout << "\n";
    for (int i = 0; i < n; i++) { // вывод массива х2
        for (int j = 0; j < n; j++) {
            cout << randoms[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
