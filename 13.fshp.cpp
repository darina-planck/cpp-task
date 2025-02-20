#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept> // Для std::invalid_argument
using namespace std;

// Константы для денежной системы
const int pence_in_shilling = 12;    // Пенсы в шиллинге
const int shilling_in_pound = 20;   // Шиллинги в фунте
const int pence_in_pound = pence_in_shilling * shilling_in_pound; // Пенсы в фунте

// Структура для представления денежной суммы
struct Money {
    int pounds;  // Фунты
    int shillings; // Шиллинги
    int pence;     // Пенсы
};

// Функция для нормализации значения
void normalize(Money &money) {
    if (money.pence >= pence_in_shilling) {// Если количество пенсов больше или равно 12, они преобразуются в шиллинги
        money.shillings += money.pence / pence_in_shilling;
        money.pence %= pence_in_shilling;
    }
    if (money.shillings >= shilling_in_pound) { // Если количество шиллингов больше или равно 20, они преобразуются в фунты
        money.pounds += money.shillings / shilling_in_pound;
        money.shillings %= shilling_in_pound;
    }
}

// Функция для увеличения суммы на заданное количество фунтов, шиллингов и пенсов
Money add(Money a, int pounds, int shillings, int pence) {
    Money result = a;
    result.pounds += pounds;
    result.shillings += shillings;
    result.pence += pence;
    normalize(result);
    return result;
}

// Функция для сложения двух денежных сумм
Money add(Money a, Money b) {
    Money result;
    result.pounds = a.pounds + b.pounds;
    result.shillings = a.shillings + b.shillings;
    result.pence = a.pence + b.pence;
    normalize(result);
    return result;
}

// Функция для вычитания двух денежных сумм
Money subtract(Money a, Money b) {
    Money result;
    result.pounds = a.pounds - b.pounds;
    result.shillings = a.shillings - b.shillings;
    result.pence = a.pence - b.pence;

    // Нормализация после вычитания
    if (result.pence < 0) {
        result.shillings -= (abs(result.pence) + pence_in_shilling - 1) / pence_in_shilling;
        result.pence = (result.pence + pence_in_shilling) % pence_in_shilling;
    }
    if (result.shillings < 0) {
        result.pounds -= (abs(result.shillings) + shilling_in_pound - 1) / shilling_in_pound;
        result.shillings = (result.shillings + shilling_in_pound) % shilling_in_pound;
    }

    return result;
}

// Функция для перевода денежной суммы в пенсы
int toPence(const Money &money) {
    return money.pounds * pence_in_pound + money.shillings * pence_in_shilling + money.pence;
}

// Функция для вывода денежной суммы в формате "99-99-99"
void printMoney(const Money &money) {
    cout << money.pounds << "-" << money.shillings << "-" << money.pence;
}

// Функция для вычисления среднего значения
Money calculateAverage(const vector<Money> &moneyList) {
    Money total = {0, 0, 0};
    for (const auto &money : moneyList) {
        total = add(total, money);
    }
    int n = moneyList.size();
    Money average = total;
    average.pounds /= n;
    average.shillings = (total.shillings + (total.pounds % n) * shilling_in_pound) / n;
    average.pence = (total.pence + (total.shillings % n) * pence_in_shilling) / n;
    normalize(average);
    return average;
}

// Функция для поиска наиболее близких и наиболее далеких пар
void findClosestAndFarthestPairs(const vector<Money> &moneyList, int closestPair[2], int farthestPair[2]) {
    double minDiff = numeric_limits<double>::max();
    double maxDiff = numeric_limits<double>::min();

    for (size_t i = 0; i < moneyList.size(); ++i) {
        for (size_t j = i + 1; j < moneyList.size(); ++j) {
            double diff = abs(toPence(moneyList[i]) - toPence(moneyList[j]));
            if (diff < minDiff) {
                minDiff = diff;
                closestPair[0] = i;
                closestPair[1] = j;
            }
            if (diff > maxDiff) {
                maxDiff = diff;
                farthestPair[0] = i;
                farthestPair[1] = j;
            }
        }
    }
}

// Главная функция программы
int main() {
    while (true) {
        cout << "\nМеню:\n";
        cout << "a. Проверка корректности значения\n";
        cout << "b. Увеличение суммы на заданное количество пенсов, шиллингов, фунтов\n";
        cout << "c. Сложение двух денежных сумм\n";
        cout << "d. Вычитание двух денежных сумм\n";
        cout << "e. Перевод суммы в пенсы\n";
        cout << "1. Найти среднее значение набора сумм\n";
        cout << "2. Найти наиболее близкие и наиболее далекие пары сумм\n";
        cout << "q. Выход\n";

        char choice;
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 'q') {
            break;
        }

        switch (choice) {
            case 'a': {
                Money input;
                cout << "Введите сумму (фунты шиллинги пенсы): ";
                cin >> input.pounds >> input.shillings >> input.pence;
                normalize(input);
                cout << "Нормализованная сумма: ";
                printMoney(input);
                cout << endl;
                break;
            }
            case 'b': {
                Money input;
                int pounds, shillings, pence;
                cout << "Введите исходную сумму (фунты шиллинги пенсы): ";
                cin >> input.pounds >> input.shillings >> input.pence;
                cout << "Введите增加值 (фунты шиллинги пенсы): ";
                cin >> pounds >> shillings >> pence;
                Money result = add(input, pounds, shillings, pence);
                cout << "Результат: ";
                printMoney(result);
                cout << endl;
                break;
            }
            case 'c': {
                Money sum1, sum2;
                cout << "Введите первую сумму (фунты шиллинги пенсы): ";
                cin >> sum1.pounds >> sum1.shillings >> sum1.pence;
                cout << "Введите вторую сумму (фунты шиллинги пенсы): ";
                cin >> sum2.pounds >> sum2.shillings >> sum2.pence;
                Money result = add(sum1, sum2);
                cout << "Сумма: ";
                printMoney(result);
                cout << endl;
                break;
            }
            case 'd': {
                Money sum1, sum2;
                cout << "Введите первую сумму (фунты шиллинги пенсы): ";
                cin >> sum1.pounds >> sum1.shillings >> sum1.pence;
                cout << "Введите вторую сумму (фунты шиллинги пенсы): ";
                cin >> sum2.pounds >> sum2.shillings >> sum2.pence;
                Money result = subtract(sum1, sum2);
                cout << "Разность: ";
                printMoney(result);
                cout << endl;
                break;
            }
            case 'e': {
                Money input;
                cout << "Введите сумму (фунты шиллинги пенсы): ";
                cin >> input.pounds >> input.shillings >> input.pence;
                int penceValue = toPence(input);
                cout << "Сумма в пенсах: " << penceValue << endl;
                break;
            }
            case '1': {
                int N;
                cout << "Введите количество сумм: ";
                cin >> N;
                vector<Money> moneyList(N);
                cout << "Введите суммы (фунты шиллинги пенсы):\n";
                for (int i = 0; i < N; ++i) {
                    cin >> moneyList[i].pounds >> moneyList[i].shillings >> moneyList[i].pence;
                    normalize(moneyList[i]);
                }
                Money average = calculateAverage(moneyList);
                cout << "Среднее значение: ";
                printMoney(average);
                cout << endl;
                break;
            }
            case '2': {
                int N;
                cout << "Введите количество сумм: ";
                cin >> N;
                vector<Money> moneyList(N);
                cout << "Введите суммы (фунты шиллинги пенсы):\n";
                for (int i = 0; i < N; ++i) {
                    cin >> moneyList[i].pounds >> moneyList[i].shillings >> moneyList[i].pence;
                    normalize(moneyList[i]);
                }

                int closestPair[2] = {0, 1};
                int farthestPair[2] = {0, 1};
                findClosestAndFarthestPairs(moneyList, closestPair, farthestPair);

                cout << "\nНаиболее близкие пары:\n";
                cout << "Сумма 1: "; printMoney(moneyList[closestPair[0]]); cout << endl;
                cout << "Сумма 2: "; printMoney(moneyList[closestPair[1]]); cout << endl;

                cout << "\nНаиболее далекие пары:\n";
                cout << "Сумма 1: "; printMoney(moneyList[farthestPair[0]]); cout << endl;
                cout << "Сумма 2: "; printMoney(moneyList[farthestPair[1]]); cout << endl;
                break;
            }
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}