#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool err(int n, int maxRange = -1)
{
    if (n < 0)
    {
        cout << "Ошибка: введенное число меньше нуля. Попробуйте еще раз.\n";
        return true;
    }
    else if (n == 0)
    {
        cout << "Ошибка: введенное число равно нулю. Попробуйте еще раз.\n";
        return true;
    }
    else if (maxRange != -1 && n > maxRange)
    {
        cout << "Ошибка: введенное число выходит за допустимый диапазон (1 - " << maxRange << "). Попробуйте еще раз.\n";
        return true;
    }
    return false;
}

int main()
{
    string massage;
    vector<unsigned char> numbers = {};
    cout << "Введите строку " << "\n";
    getline(cin, massage);

    for (char c : massage)
    {
        if (isdigit(c))
        {
            numbers.push_back(c); 
        }
    }

    if (numbers.empty())
    {
        cout << "Введенная строка не содержит цифр.\n";
        return 1;
    }

    int answer = 0, number, start, end;

    cout << "Вывести число или диапазон?" << "\n";
    cout << "Если число введите 1, если диапазон введите 2" << "\n";

    cin >> answer;
    if (err(answer, 2)) return 1; // не выходит за пределы 1 и 2

    if (answer == 1)
    {
        cout << "Ведите номер цифры, которую хотите вывести:  " << "\n";
        cin >> number;
        err(number); // проверка на ошибки
        if (number > numbers.size()) {
            cout << "Ошибка: введенное число выходит за допустимый диапазон. Попробуйте еще раз.\n";
            return 1;
    }
        if (err(number) == 0)
        {
            cout << "Цифрой номер " << number << " является " << numbers[number - 1] << "\n";
        }
    }
    else
    {
        cout << "Введите начало диапазона: ";
        cin >> start;
        if (err(start, numbers.size())) return 1; // проверка на то что start находится в диапазоне от 1 до numbers.size()
        // чтобы не вышло за диапазон выходящий за пределы количества цифр в строке

        cout << "Введите конец диапазона: ";
        cin >> end;
        if (err(end, numbers.size())) return 1; // то же самое что и со start

        if (start > end) {
            cout << "Ошибка: начало диапазона не может быть больше конца.\n";
            return 1;
        }
    }
    return 0;
}