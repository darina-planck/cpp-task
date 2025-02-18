#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Константы
const int pence_in_shilling = 12;
const int shilling_in_pound = 20;
const int pence_in_pound = pence_in_shilling * shilling_in_pound;

struct Money {
    int pounds;
    int shillings;
    int pence;
};


Money normalizeMoney(const Money& money) {
    int totalPence = money.pounds * pence_in_pound + money.shillings * pence_in_shilling + money.pence; // вся сумма в пенсах
    int normalizedPounds = totalPence / pence_in_pound; // количество полных фунтов
    int remainingPence = totalPence % pence_in_pound; // остатки пенсов от пред. операции
    int normalizedShillings = remainingPence / pence_in_shilling; // остатки делим на кол-во пенсов в шиллинге дабы найти сколько полных щиллингов
    int normalizedPence = remainingPence % pence_in_shilling; // самые самые остатки пенсов
    return {normalizedPounds, normalizedShillings, normalizedPence}; // возвращаем фунты, шиллинги, пенсы
}

// б) Увеличение заданной суммы на заданное количество пенсов, шиллингов, фунтов
Money increaseMoney(const Money& money, int pounds = 0, int shillings = 0, int pence = 0) {
    int totalPence = money.pounds * pence_in_pound + money.shillings * pence_in_shilling + money.pence;
    totalPence += pounds * pence_in_pound + shillings * pence_in_shilling + pence;
    return normalizeMoney({0, 0, totalPence});
}

// в) Сложение двух денежных сумм
Money addMoney(const Money& money1, const Money& money2) {
    int totalPence = money1.pounds * pence_in_pound + money1.shillings * pence_in_shilling + money1.pence;
    totalPence += money2.pounds * pence_in_pound + money2.shillings * pence_in_shilling + money2.pence;
    return normalizeMoney({0, 0, totalPence});
}

// г) Вычисление разности денежных сумм
Money subtractMoney(const Money& money1, const Money& money2) {
    int totalPence1 = money1.pounds * pence_in_pound + money1.shillings * pence_in_shilling + money1.pence;
    int totalPence2 = money2.pounds * pence_in_pound + money2.shillings * pence_in_shilling + money2.pence;
    int totalPence = totalPence1 - totalPence2;
    if (totalPence < 0) {
        throw std::invalid_argument("Разность не может быть отрицательной");
    }
    return normalizeMoney({0, 0, totalPence});
}

// д) Перевод денежной суммы в пенсы
int toPence(const Money& money) {
    return money.pounds * pence_in_pound + money.shillings * pence_in_shilling + money.pence;
}


// Функция для вывода денежной суммы в формате «99–99–99»
std::string formatMoney(const Money& money) {
    return (std::to_string(money.pounds) + "–" + std::to_string(money.shillings) + "–" + std::to_string(money.pence));
}

int main() {
    int choice;
    Money money1, money2, result;
    int pounds, shillings, pence;

    while (true) {
        cout << "\nВыберите операцию:\n";
        cout << "1. Увеличение суммы\n";
        cout << "2. Сложение двух сумм\n";
        cout << "3. Вычисление разности двух сумм\n";
        cout << "4. Перевод суммы в пенсы\n";
        cout << "5. Выйти\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 5) {
            break;
        }

        switch (choice) {
            case 1:
                cout << "Введите исходную сумму (фунты шиллинги пенсы): ";
                cin >> money1.pounds >> money1.shillings >> money1.pence;
                cout << "Введите количество для увеличения (фунты шиллинги пенсы): ";
                cin >> pounds >> shillings >> pence;
                result = increaseMoney(money1, pounds, shillings, pence);
                cout << "Увеличенная сумма: " << formatMoney(result) << endl;
                break;

            case 2:
                cout << "Введите первую сумму (фунты шиллинги пенсы): ";
                cin >> money1.pounds >> money1.shillings >> money1.pence;
                cout << "Введите вторую сумму (фунты шиллинги пенсы): ";
                cin >> money2.pounds >> money2.shillings >> money2.pence;
                result = addMoney(money1, money2);
                cout << "Сумма: " << formatMoney(result) << endl;
                break;

            case 3:
                cout << "Введите первую сумму (фунты шиллинги пенсы): ";
                cin >> money1.pounds >> money1.shillings >> money1.pence;
                cout << "Введите вторую сумму (фунты шиллинги пенсы): ";
                cin >> money2.pounds >> money2.shillings >> money2.pence;
                try {
                    result = subtractMoney(money1, money2);
                    cout << "Разность: " << formatMoney(result) << endl;
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                break;

            case 4:
                cout << "Введите сумму (фунты шиллинги пенсы): ";
                cin >> money1.pounds >> money1.shillings >> money1.pence;
                int totalPence = toPence(money1);
                cout << "Перевод в пенсы: " << totalPence << " пенсов" << endl;
                break;
        }
    }

    return 0;
}