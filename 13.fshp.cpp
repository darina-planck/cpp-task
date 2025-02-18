#include <iostream>
#include <vector>
#include <string>

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
// Функция для вывода денежной суммы в формате «99–99–99»
std::string formatMoney(const Money& money) {
    return (std::to_string(money.pounds) + "–" + std::to_string(money.shillings) + "–" + std::to_string(money.pence));
}

int main() {
    int pounds, shillings, pence;

    // Ввод значений для тестирования
    std::cout << "Введите количество фунтов: ";
    std::cin >> pounds;
    std::cout << "Введите количество шиллингов: ";
    std::cin >> shillings;
    std::cout << "Введите количество пенсов: ";
    std::cin >> pence;

    Money input = {pounds, shillings, pence};
    Money result = normalizeMoney(input);

    // Вывод результата нормализации в формате «99–99–99»
    std::cout << "Нормализованная сумма: " << formatMoney(result) << std::endl;

    return 0;
}