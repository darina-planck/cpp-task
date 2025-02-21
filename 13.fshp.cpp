#include <iostream>
#include <vector>
#include <cmath>
#include <limits> // Для cin.ignore()
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
    if (money.pence >= pence_in_shilling) {
        money.shillings += money.pence / pence_in_shilling;
        money.pence %= pence_in_shilling;
    }
    if (money.shillings >= shilling_in_pound) {
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

    // Проверка на отрицательную сумму
    if (result.pounds < 0 || (result.pounds == 0 && result.shillings < 0) || (result.pounds == 0 && result.shillings == 0 && result.pence < 0)) {
        cout << "Ошибка: Разность не может быть отрицательной." << endl;
        return {0, 0, 0}; // Возвращаем нулевую сумму
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

// Функция для безопасного чтения суммы Money с проверкой формата ввода
bool readMoney(Money &money) {
    while (true) {
        if (!(cin >> money.pounds >> money.shillings >> money.pence)) { // Проверяем, является ли ввод числом
            cout << "Ошибка: Введите три целых числа через пробел (фунты шиллинги пенсы)." << endl;
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Удаляем неверные данные из буфера
            continue; // Повторяем попытку ввода
        }
        // Если ввод успешен, проверяем, что после трех чисел нет лишних символов
        if (cin.peek() != '\n') { // cin.peek() проверяет следующий символ в потоке
            cout << "Ошибка: Введите ровно три числа через пробел (фунты шиллинги пенсы)." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Удаляем лишние символы
            continue; // Повторяем попытку ввода
        }
        break; // Если всё хорошо, выходим из цикла
    }
    return true;
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
                if (!readMoney(input)) {
                    break;
                }
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
                if (!readMoney(input)) {
                    break;
                }
                cout << "Введите增加值 (фунты шиллинги пенсы): ";
                if (!(cin >> pounds >> shillings >> pence)) {
                    cout << "Ошибка: Введите три целых числа через пробел (фунты шиллинги пенсы)." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                Money result = add(input, pounds, shillings, pence);
                cout << "Результат: ";
                printMoney(result);
                cout << endl;
                break;
            }
            case 'c': {
                Money sum1, sum2;
                cout << "Введите первую сумму (фунты шиллинги пенсы): ";
                if (!readMoney(sum1)) {
                    break;
                }
                cout << "Введите вторую сумму (фунты шиллинги пенсы): ";
                if (!readMoney(sum2)) {
                    break;
                }
                Money result = add(sum1, sum2);
                cout << "Сумма: ";
                printMoney(result);
                cout << endl;
                break;
            }
            case 'd': {
                Money sum1, sum2;
                cout << "Введите первую сумму (фунты шиллинги пенсы): ";
                if (!readMoney(sum1)) {
                    break;
                }
                cout << "Введите вторую сумму (фунты шиллинги пенсы): ";
                if (!readMoney(sum2)) {
                    break;
                }

                Money result = subtract(sum1, sum2);

                // Если разность стала отрицательной, выводим сообщение об ошибке
                if (result.pounds < 0 || (result.pounds == 0 && result.shillings < 0) || (result.pounds == 0 && result.shillings == 0 && result.pence < 0)) {
                    cout << "Ошибка: Разность не может быть отрицательной." << endl;
                } else {
                    cout << "Разность: ";
                    printMoney(result);
                    cout << endl;
                }
                break;
            }
            case 'e': {
                Money input;
                cout << "Введите сумму (фунты шиллинги пенсы): ";
                if (!readMoney(input)) {
                    break;
                }
                int penceValue = toPence(input);
                cout << "Сумма в пенсах: " << penceValue << endl;
                break;
            }
            case '1': {
                int N;
                cout << "Введите количество сумм: ";
                if (!(cin >> N) || N <= 0) { // Проверяем, что введено число больше 0
                    cout << "Ошибка: Введите положительное целое число." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                vector<Money> moneyList(N);
                cout << "Введите суммы (фунты шиллинги пенсы):\n";
                for (int i = 0; i < N; ++i) {
                    cout << "Сумма " << (i + 1) << ": ";
                    if (!readMoney(moneyList[i])) {
                        --i; // Повторяем попытку ввода
                        continue;
                    }
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
                if (!(cin >> N) || N <= 0) { // Проверяем, что введено число больше 0
                    cout << "Ошибка: Введите положительное целое число." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                vector<Money> moneyList(N);
                cout << "Введите суммы (фунты шиллинги пенсы):\n";
                for (int i = 0; i < N; ++i) {
                    cout << "Сумма " << (i + 1) << ": ";
                    if (!readMoney(moneyList[i])) {
                        --i; // Повторяем попытку ввода
                        continue;
                    }
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