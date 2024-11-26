#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    // Открываем файл для чтения
    ifstream file("7.txt");

    if (!file.is_open()) { // проверка на ошибку
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    // Создаем словарь для хранения данных
    map<string, vector<int>> data; // ключ строка, значение вектор цифр

    string line;
    while (getline(file, line)) { // пока есть строки в файле, они добавляются в переменную лайн
        istringstream iss(line); // создание потока из строки
        string name; // строка имя
        int grade; // переменная для оценок

        // Читаем имя (включая пробелы)
        getline(iss, name, ' '); // iss это почти тоже самое что cin // тут name считывает фамилию
        string middleName;
        getline(iss, middleName, ' '); // считываем инициалы имени
        string lastName;
        getline(iss, lastName, ' '); // считываем инициалы отчества
        name = name + " " + middleName + " " + lastName;

        // Читаем оценки и добавляем их в вектор
        vector<int> grades;
        while (iss >> grade) {
            grades.push_back(grade);
        }
        // Добавляем данные в словарь
        data[name] = grades;
    }
    // Закрываем файл
    file.close();

    // Выводим данные из словаря
    for (const auto& entry : data) {
        cout << entry.first << ": ";
        for (int grade : entry.second) {
            cout << grade << " ";
        }
        cout << endl;
    }

    return 0;
}
