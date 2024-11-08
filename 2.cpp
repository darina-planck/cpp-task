#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
using namespace std;

int err(int n) {
    if (n < 0)
    {
        cout << "Количество комнат не может быть меньше 0." << "\n";
    }
    else if (n == 0)
    {
        cout << "Длина провода равна 0." << "\n";
    }
    return 0;
};

int main() {

    auto n = 0;
    int x;
    int mindl = 10000, commutator = 0;
Step1:
    cout << "\n" << "Введите количество комнат в которые поставить телефоны ";
    cin >> n;
    if (cin.fail())
    { // проверка на не число
        cout << "Неправильные входные данные. Попробуйте еще раз.";
        cin.clear();
        cin.ignore();
        goto Step1;
    }

    cout << err(n);
Step2:
    vector<int> number;

    cout << "\n" << "Введите номера комнат ";
    int i = 0;
    while (i < n)
    {
        cin >> x;
        if (cin.fail() || x <= 0)
        { // проверка на не число
            cout << "Неправильные входные данные. Попробуйте еще раз.";
            cin.clear();
            cin.ignore();
            goto Step2;
        }
        number.push_back(x);
        i++;
    }

    std::vector<int> min_length; // массив в котором будут храниться длина провода

    int min = *min_element(begin(number), end(number));
    int max = *max_element(begin(number), end(number)); //

    for (int i = min; i <= max; i++)
    { // i - номер комнаты у которой ставится коммутатор
        int m = 0;
        int a = 0;
        for (int j = 0; j < n; j++)
        { // n - количество комнат которые нуждаются в телефоне
            m = abs(i - number[j]);
            a += m; // a - длина провода
        }
        if (a < mindl)
        {
            mindl = a;
            commutator = i;
        }
        min_length.push_back(a);
    }

    int minWire = *std::min_element(begin(min_length), end(min_length));

    for (int i = 0; i < min_length.size(); i++)
    {
        if (min_length[i] == minWire)
        {
            cout << "длина провода: " << minWire << "\n";
            cout << "номер комнаты: " << commutator << "\n";
            break;
        }
    }
    return 0;
}