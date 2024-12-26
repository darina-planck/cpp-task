#include <iostream>
#include <fstream> // Подключение библиотеки для работы с файлами
#include <sstream> // Подключение библиотеки для обработки строк в потоках
#include <string>
#include <vector> // Подключение библиотеки для работы с контейнером vector
#include <limits>// Подключение библиотеки для работы с числовыми ограничениями
#include <iomanip> // Подключаем библиотеку для форматирования вывода

using namespace std;

const int MAX_GRADE = 5; // максимальная оценка

// Структура для хранения данных об ученике
struct Student {
    string surname; // фамилия ученика
    string initials; // инициалы ученика
    vector<int> grades; // вектор для зранения оценок ученика
};

// Функция для загрузки списка учеников из файла
void loadStudents(vector<Student>& students) {
    cout << "Введите имя входного файла (.txt, .csv, .json): "; // запрашиваем имя файла
    string filename;
    getline(cin, filename); // считываем имя файла
    ifstream infile(filename); // открываем файл
    if (!infile) { // проверка открытия файла
        cout << "Не удалось открыть файл. Начинаем с пустого списка." << endl;
        return;
    }
    string line;
    // построчное чтение данных из файла
    while (getline(infile, line)) { // считываем строку из потока и записывает ее в переменную line
        istringstream iss(line); // создание потока для обработки строки
        Student student;
        iss >> student.surname; // считываем фамилии учеников
        string word;
        // Чтение инициалов
        while (iss >> word && !isdigit(word[0])) { // считываем слово из потока и записываем в переменную word
            if (!student.initials.empty()) student.initials += " "; // проверка что строка не пустая
            student.initials += word; // добавление инициалов
        }
        // Чтение оценок
        if (isdigit(word[0])) student.grades.push_back(stoi(word)); // проверка на цифру(первого символа)
        while (iss >> word) {
            if (isdigit(word[0])) student.grades.push_back(stoi(word)); // добавление оценки
        }
        students.push_back(student); // добавление ученика в вектор
    }
}

// функция для сохранения списка учеников в файл
void saveStudents(const vector<Student>& students) {
    cout << "Введите имя файла для сохранения (.txt, .csv, .json): "; // запрашиваем имя файла
    string filename;
    getline(cin, filename); //считываем имя файла
    ofstream outfile(filename); // открытие файла для записи
    if (!outfile) { // проверка открытия файла
        cout << "Не удалось открыть файл для записи." << endl;
        return;
    }
    // запись данных о каждом ученике в файл
    for (const auto& student : students) {
        outfile << student.surname << " " << student.initials; // запись фамилии и инициалов
        for (int grade : student.grades)
            outfile << " " << grade; // запись оценок
        outfile << endl;
    }
    cout << "Данные успешно сохранены в файл " << filename << endl;
}

// функция добавления нового ученика
void addStudent(vector<Student>& students) {
    Student newStudent; //создание нового ученика
    cout << "Введите фамилию ученика: ";
    getline(cin, newStudent.surname); // считываем фамилию
    cout << "Введите инициалы ученика (например, А. Б.): ";
    getline(cin, newStudent.initials); // считываем инициалы
    cout << "Введите количество оценок: ";
    int numGrades;
    while (!(cin >> numGrades) || numGrades < 0) { // проверка ввода количества оценок
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // очистка потока
    for (int i = 0; i < numGrades; ++i) {
        cout << "Введите оценку " << i + 1 << ": ";
        int grade;
        while (!(cin >> grade) || grade < 1 || grade > MAX_GRADE) { // проверка ввода оценки
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        newStudent.grades.push_back(grade); // добавление оценки в список
    }
    students.push_back(newStudent); // добавление ученика в вектор
    cout << "Ученик успешно добавлен." << endl;
}

void addGrades(vector<Student>& students) { // функция для обавления оценок ученику
    if (students.empty()) { // проверка на пустоту список
        cout << "Список учеников пуст." << endl;
        return;
    }
    // выводим список учеников для выбора
    cout << "Выберите ученика для добавления оценок:" << endl;
    for (size_t i = 0; i < students.size(); ++i)
        cout << i + 1 << ". " << students[i].surname << " " << students[i].initials << endl;
    int choice;
    // получаем номер выбранного ученика
    while (!(cin >> choice) || choice < 1 || choice > students.size()) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear(); // сбрасываем состояние потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    Student& student = students[choice - 1]; // ссылаемся на выбранного ученника
    cout << "Введите количество добавляемых оценок: ";
    int numGrades;
    // получаем количество оценок
    while (!(cin >> numGrades) || numGrades < 1) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    for (int i = 0; i < numGrades; ++i) { // добавляем каждую оценку
        cout << "Введите оценку " << i + 1 << ": ";
        int grade;
        while (!(cin >> grade) || grade < 1 || grade > MAX_GRADE) { // проверка корректность оценки
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        student.grades.push_back(grade); // добавляем оценку в список
    }
    cout << "Оценки успешно добавлены." << endl;
}

void deleteStudentOrGrades(vector<Student>& students) { // функция удаления ученика или его оценок
    if (students.empty()) { // проверяем на пустоту список
        cout << "Список учеников пуст." << endl;
        return;
    }
    // предлагаем выбрать действие
    cout << "1. Удалить ученика\n2. Удалить оценки ученика\nВыберите действие: ";
    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    if (choice == 1) { // удаление ученикаx
        cout << "Выберите ученика для удаления:" << endl;
        for (size_t i = 0; i < students.size(); ++i)
            cout << i + 1 << ". " << students[i].surname << " " << students[i].initials << endl;
        int idx;
        while (!(cin >> idx) || idx < 1 || idx > students.size()) {
            // проверка корректность выбора
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        students.erase(students.begin() + idx - 1); // удаляем ученика из списка
        cout << "Ученик успешно удален." << endl;
    }
    else { // удаление оценок ученика
        cout << "Выберите ученика для удаления оценок:" << endl;
        for (size_t i = 0; i < students.size(); ++i)
            cout << i + 1 << ". " << students[i].surname << " " << students[i].initials << endl;
        int idx;
        while (!(cin >> idx) || idx < 1 || idx > students.size()) { // проверяем корректность выбора
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        Student& student = students[idx - 1];
        if (student.grades.empty()) { // проверка наличия оценок у ученика
            cout << "У ученика нет оценок." << endl;
            return;
        }
        cout << "Оценки ученика:" << endl; // выводим список оценок для удаления
        for (size_t i = 0; i < student.grades.size(); ++i)
            cout << i + 1 << ". " << student.grades[i] << endl;
        cout << "Введите номер оценки для удаления (0 для удаления всех оценок): ";
        int gradeIdx;
        while (!(cin >> gradeIdx) || gradeIdx < 0 || gradeIdx > student.grades.size()) { // проверяем корректность выбора
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        if (gradeIdx == 0) { //удаляем все оценки
            student.grades.clear();
            cout << "Все оценки удалены." << endl;
        } else { // удалаем выбранную оценку
            student.grades.erase(student.grades.begin() + gradeIdx - 1);
            cout << "Оценка успешно удалена." << endl;
        }
    }
}

void modifyGrade(vector<Student>& students) { // функция для изменения оценки
    if (students.empty()) { // проверяем список на пустоту
        cout << "Список учеников пуст." << endl;
        return;
    }
    cout << "Выберите ученика для изменения оценки:" << endl;
    for (size_t i = 0; i < students.size(); ++i)
        cout << i + 1 << ". " << students[i].surname << " " << students[i].initials << endl;
    int idx;
    while (!(cin >> idx) || idx < 1 || idx > students.size()) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    Student& student = students[idx - 1];
    if (student.grades.empty()) {
        cout << "У ученика нет оценок." << endl;
        return;
    }
    cout << "Оценки ученика:" << endl;
    for (size_t i = 0; i < student.grades.size(); ++i)
        cout << i + 1 << ". " << student.grades[i] << endl;
    cout << "Введите номер оценки для изменения: ";
    int gradeIdx;
    while (!(cin >> gradeIdx) || gradeIdx < 1 || gradeIdx > student.grades.size()) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    cout << "Введите новую оценку: ";
    int newGrade;
    while (!(cin >> newGrade) || newGrade < 1 || newGrade > MAX_GRADE) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    student.grades[gradeIdx - 1] = newGrade;
    cout << "Оценка успешно изменена." << endl;
}

void calculateFinalGrade(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Список учеников пуст." << endl;
        return;
    }
    cout << "1. Посчитать итоговую оценку одного ученика\n2. Посчитать итоговые оценки всех учеников\nВыберите действие: ";
    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Недопустимый ввод. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    if (choice == 1) {
        cout << "Выберите ученика:" << endl;
        for (size_t i = 0; i < students.size(); ++i)
            cout << i + 1 << ". " << students[i].surname << " " << students[i].initials << endl;
        int idx;
        while (!(cin >> idx) || idx < 1 || idx > students.size()) {
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        const Student& student = students[idx - 1];
        if (student.grades.empty()) {
            cout << "У ученика нет оценок." << endl;
            return;
        }
        double sum = 0;
        for (int grade : student.grades)
            sum += grade;
        cout << "Итоговая оценка ученика " << student.surname << " " << student.initials << ": " << sum / student.grades.size() << endl;
    }
    else {
        for (const auto& student : students) {
            if (student.grades.empty()) {
                cout << "У ученика " << student.surname << " " << student.initials << " нет оценок." << endl;
                continue;
            }
            double sum = 0;
            for (int grade : student.grades)
                sum += grade;
            cout << "Итоговая оценка ученика " << student.surname << " " << student.initials << ": " << sum / student.grades.size() << endl;
        }
    }
}

// Функция для вывода списка учеников в консоль
void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Список учеников пуст." << endl;
        return;
    }
    cout << setw(20) << left << "Фамилия"
         << setw(10) << "Инициалы"
         << "Оценки" << endl;
    cout << string(50, '-') << endl;
    for (const auto& student : students) {
        cout << setw(20) << left << student.surname
             << setw(10) << student.initials;
        if (student.grades.empty()) {
            cout << "Нет оценок";
        } else {
            for (size_t i = 0; i < student.grades.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << student.grades[i];
            }
        }
        cout << endl;
    }
}

// отображение меню
void displayMenu() {
    cout << "\n  == Электронный дневник == \n"
        << "1. Добавить нового ученика\n"
        << "2. Добавить оценки для ученика\n"
        << "3. Удалить ученика или оценки\n"
        << "4. Изменить оценку у ученика\n"
        << "5. Посчитать итоговую оценку\n"
        << "6. Сохранить изменения в файл\n"
        << "7. Вывести список учеников\n"
        << "8. Выход\n\n"
        << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian"); // установка локали для корректного отображения русского языка
    vector<Student> students; // вектор для хранения списка учеников
    loadStudents(students); // загрузка файлов из файла
    int choice;
    do {
        displayMenu(); // функция для отображения меню
        while (!(cin >> choice) || choice < 1 || choice > 8) { // проверка выбора пользователя
            cout << "Недопустимый ввод. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // очистка потока ввода
        switch (choice) {
        // выполнение действия в зависимости от выбора пользователя
        case 1: addStudent(students); break;
        case 2: addGrades(students); break;
        case 3: deleteStudentOrGrades(students); break;
        case 4: modifyGrade(students); break;
        case 5: calculateFinalGrade(students); break;
        case 6: saveStudents(students); break;
        case 7: displayStudents(students); break;
        case 8: cout << "Выход из программы." << endl; break;
        }
    } while (choice != 8); // продолжение рыботы, пока не будет выбран пункт "выход"

    // Создаем новый файл с оценками каждого студента
    ofstream outFile("new_students.txt"); // Имя нового файла
    if (outFile.is_open()) {
        // Записываем заголовки колонок
        outFile << setw(20) << left << "Фамилия"
                << setw(10) << "Инициалы"
                << "Оценки" << endl;
        outFile << string(50, '-') << endl; // Разделительная строка

        // Обрабатываем каждого студента
        for (const auto& student : students) {
            outFile << setw(20) << left << student.surname // Записываем фамилию
                    << setw(10) << student.initials;       // Записываем инициалы
            if (student.grades.empty()) { // Если нет оценок
                outFile << "Нет оценок";
            } else { // Если оценки есть
                for (size_t i = 0; i < student.grades.size(); ++i) {
                    if (i > 0) outFile << ", ";
                    outFile << student.grades[i]; // Записываем оценку
                }
            }
            outFile << endl;
        }
        outFile.close(); // Закрываем файл
        cout << "Оценки студентов сохранены в файл 'new_students.txt'." << endl; // Уведомление об успешной записи
    } else {
        cerr << "Ошибка: не удалось сохранить оценки студентов." << endl; // Уведомление об ошибке открытия файла
    }
    return 0;
}
