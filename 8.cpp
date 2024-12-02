#include <iostream>
#include <map>
#include <fstream>
using namespace std;

int main() {
    int m1, m2, m3, m4, m5, m6, m7, m8;
    map<int, int> answer;
    cout << "Отвечать можете 0 или 1\n";
    cout << "Вы любите 111б-пио?\n";
    cin >> m1;
    answer[1] = m1;
    cout << "Вы сегодня опоздали?\n";
    cin >> m2;
    answer[2] = m2;
    cout << "Вы выспались сегодня?\n";
    cin >> m3;
    answer[3] = m3;
    cout << "Хотите ли Вы уйти?\n";
    cin >> m4;
    answer[4] = m4;
    cout << "Вы любите кофе?\n";
    cin >> m5;
    answer[5] = m5;
    cout << "А чай?\n";
    cin >> m6;
    answer[6] = m6;
    cout << "Любите кошек?\n";
    cin >> m7;
    answer[7] = m7;
    cout << "Да или нет?\n";
    cin >> m8;
    answer[8] = m8;

    cout << "Хотите изменить ответ на вопрос? |0 or 1|\n";
    int n;
    cin >> n;
    if (n == 1) {
        cout << "Какой вопрос хотите изменить?\n";
        int t;
        cin >> t;
        cout << "Введите новый ответ на вопрос\n";
        int b;
        cin >> b;
        answer[t] = b;
        cout << "Ответ сохранен!\n";
    }

    // Кодирование ответов в 1 байт
    unsigned char result = 0; // 1 байт
    for (int i = 1; i <= 8; i++) {
        if (answer[i] == 1) {
            result |= (1 << (i - 1)); // Устанавливаем i-й бит
        }
    }

    // Сохранение в файл
    ofstream file("8.bin", ios::binary);
    file.write(reinterpret_cast<const char*>(&result), sizeof(result));
    file.close();

    cout << "Ответы сохранены в файл размером 1 байт!\n";
    return 0;
}
