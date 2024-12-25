#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

// Прототипы функций
struct Book; // Объявляем структуру Book

vector<Book> filter_books_by_price(const vector<Book>& books, float min_price, float max_price);
void add_book(vector<Book>& books);
void delete_book(vector<Book>& books);
void merge_books(const string& file_path, vector<Book>& books);

// Определение структуры
struct Book { // Структура Book представляет книгу и содержит поля для хранения названия, автора, издательства, года издания и цены.
    string title;
    string author;
    string publisher;
    int year;
    float price;
};

// Функция для чтения данных из файла
vector<Book> load_books(const string& file_path) {
    vector<Book> books;
    ifstream file(file_path);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream stream(line);
            Book book;

            // Считываем данные
            getline(stream, book.title, '\t');      // Считываем название книги (до табуляции)
            getline(stream, book.author, '\t');    // Считываем автора (до табуляции)
            getline(stream, book.publisher, '\t'); // Считываем издательство (до табуляции)
            stream >> book.year;                   // Считываем год издания
            stream >> book.price;                  // Считываем цену книги

            // Убираем оставшиеся пробелы в потоке
            stream.ignore(numeric_limits<streamsize>::max(), '\n');

            books.push_back(book);
        }
        file.close();
    } else {
        cout << "Не удалось открыть файл!" << endl;
    }

    return books;
}

// Функция для сохранения данных в файл
// Эта функция открывает файл для записи и сохраняет данные о книгах из вектора books в файл. Каждая книга записывается в одну строку, разделенную табуляциями.
void save_books(const string& file_path, const vector<Book>& books) {
    ofstream file(file_path);

    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.title << "\t" << "      " << book.author << "\t" << "      "<< book.publisher << "\t"
                 << "      " <<  book.year << "      " << "\t" << static_cast<int>(book.price) << endl; // че то он через с "\t" так что навсякий случай
        }
        file.close();
    } else {
        cout << "Не удалось сохранить файл!" << endl;
    }
}

// Функция для отображения всех книг в нужном формате
// Эта функция выводит на экран информацию о всех книгах в форматированном виде. Используется библиотека iomanip для форматирования вывода.
void display_books(const vector<Book>& books) {
    cout << left << setw(20) << "Название" << setw(15) << "Автор"
         << setw(15) << "Издательство" << setw(5) << "Год" << setw(10) << "Цена" << endl;
    cout << string(70, '-') << endl;

    for (const auto& book : books) {
        cout << setw(20) << book.title << setw(15) << book.author << setw(15) << book.publisher
             << setw(5) << book.year;

        if (book.price > 0) {
            cout << setw(10) << static_cast<int>(book.price) << endl;
        } else {
            cout << setw(10) << " " << endl;  // Пустое место для нулевой цены
        }
    }
}

// Функция для фильтрации книг по диапазону цен
vector<Book> filter_books_by_price(const vector<Book>& books, float min_price, float max_price) {
    vector<Book> filtered_books;
    for (const auto& book : books) {
        if (book.price >= min_price && book.price <= max_price) {
            filtered_books.push_back(book);
        }
    }
    return filtered_books;
}

// Функция для добавления новой книги
void add_book(vector<Book>& books) {
    Book new_book;
    cout << "Введите название книги: ";
    getline(cin, new_book.title);
    cout << "Введите автора книги: ";
    getline(cin, new_book.author);
    cout << "Введите издательство книги: ";
    getline(cin, new_book.publisher);
    cout << "Введите год издания книги: ";
    cin >> new_book.year;
    cout << "Введите цену книги: ";
    cin >> new_book.price;
    cin.ignore();  // Для очистки буфера после ввода числа
    books.push_back(new_book);
}

// Функция для удаления книги по индексу
// Эта функция отображает все книги и позволяет пользователю ввести индекс книги для удаления. Если индекс корректен, книга удаляется из вектора books. (номер строки - 1)
void delete_book(vector<Book>& books) {
    display_books(books);
    int index;
    cout << "Введите индекс книги для удаления: ";
    cin >> index;
    cin.ignore();  // Для очистки буфера после ввода числа

    if (index >= 0 && index < books.size()) {
        books.erase(books.begin() + index);
        cout << "Книга удалена." << endl;
    } else {
        cout << "Некорректный индекс!" << endl;
    }
}

// Функция для добавления книг из другого файла
void merge_books(const string& file_path, vector<Book>& books) {
    string other_file_path;
    cout << "Введите путь к другому файлу: ";
    cin >> other_file_path;
    cin.ignore();  // Для очистки буфера после ввода пути

    vector<Book> other_books = load_books(other_file_path);
    books.insert(books.end(), other_books.begin(), other_books.end());
    cout << "Книги из другого файла успешно добавлены." << endl;
}

// Главная функция
int main() {
    string file_path;
    cout << "Введите путь к файлу с книгами: ";
    getline(cin, file_path);

    vector<Book> books = load_books(file_path);

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Показать все книги\n";
        cout << "2. Показать книги в диапазоне цен\n";
        cout << "3. Добавить книгу\n";
        cout << "4. Удалить книгу\n";
        cout << "5. Объединить с другим файлом\n";
        cout << "6. Сохранить и выйти\n";

        int choice;
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод! Попробуйте снова.\n";
            continue;
        }

        cin.ignore(); // Очистка буфера
        if (choice == 1) {
            display_books(books);
        } else if (choice == 2) {
            float min_price, max_price;
            cout << "Введите минимальную цену: ";
            cin >> min_price;
            cout << "Введите максимальную цену: ";
            cin >> max_price;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод! Попробуйте снова.\n";
                continue;
            }

            cin.ignore();
            vector<Book> filtered_books = filter_books_by_price(books, min_price, max_price);
            display_books(filtered_books);
        } else if (choice == 3) {
            add_book(books);
        } else if (choice == 4) {
            delete_book(books);
        } else if (choice == 5) {
            merge_books(file_path, books);
        } else if (choice == 6) {
            save_books(file_path, books);
            cout << "Данные сохранены. Выход из программы.\n";
            break;
        } else {
            cout << "Некорректный выбор! Попробуйте снова.\n";
        }
    }
    return 0;
}