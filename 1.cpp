#include <iostream>
using namespace std;

int main () {
    int a, b, c, m, n, count, percent, remainder;
    int roomLength, rollWidth;
    cout << "Введите длину комнаты: ";
    cin >> a;
    cout << "Введите ширину комнаты: ";
    cin >> b;
    cout << "Введите высоту комнаты: ";
    cin >> c;
    cout << "Введите длину рулона обоев: ";
    cin >> m;
    cout << "Введите ширину рулона обоев: ";
    cin >> n;
    if (m < c) {
        cout << "Длина рулона обоев не может быть короче высоты комнаты/n";   
    }
    roomLength = a + a + b + b;
    rollWidth = n * (m / c);
    count = roomLength / rollWidth;
    remainder = (m % c) * n;
    if (roomLength - rollWidth * count > 0) {
        count++;
        remainder += m * n - (roomLength % rollWidth) * c;
    }
    
    int procent = 100 * remainder / (count * m * n);
    cout << "Количество рулонов: " << count << "\n";
    cout << "Процент остатка " << procent << "%";
} 