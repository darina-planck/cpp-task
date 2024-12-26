#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#include <regex> // Для работы с регулярными выражениями

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
        int line_number = 0;
        regex pattern(R"((.+?)\s{2,}(.+?)\s{2,}(.+?)\s{2,}(\d{4})\s{2,}(\d+(\.\d+)?))");
        // Регулярное выражение для парсинга строки с двумя или более пробелами как разделителями

        while (getline(file, line)) {
            line_number++;
            smatch match;

            if (regex_match(line, match, pattern)) {
                Book book;
                book.title = match[1];
                book.author = match[2];
                book.publisher = match[3];
                book.year = stoi(match[4]);
                book.price = stof(match[5]);

                books.push_back(book);
            } else {
                cout << "Ошибка: Неверный формат данных в строке " << line_number << ": " << line << endl;
            }
        }

        file.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_path << endl;
    }

    return books;
}
// Функция для сохранения данных в файл
void save_books(const string& file_path, const vector<Book>& books) {
    ofstream file(file_path);

    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.title << "\t" << book.author << "\t" << book.publisher << "\t"
                 << book.year << "\t" << book.price << endl;
        }
        file.close();
    } else {
        cout << "Не удалось сохранить файл!" << endl;
    }
}

void display_books(const vector<Book>& books) {
    // Заголовки таблицы
    cout << left
         << setw(10) << "№\t"
         << setw(30) << "Название"
         << setw(30) << "Автор"
         << setw(20) << "Издательство\t"
         << setw(10) << "Год\t"
         << setw(10) << "Цена" << endl;

    cout << string(95, '-') << endl;  // Разделитель

    // Вывод данных о каждой книге с индексом
    for (size_t i = 0; i < books.size(); ++i) {
        cout << setw(10) << i  // Печатаем индекс
             << setw(30) << books[i].title
             << "\t"
             << setw(30) << books[i].author
             << "\t"
             << setw(20) << books[i].publisher
             << "\t"
             << setw(10) << books[i].year
             << fixed << setprecision(2) << setw(10) << books[i].price
             << endl;
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
void delete_book(vector<Book>& books) {
    if (books.empty()) {
        cout << "Список книг пуст. Удаление невозможно.\n";
        return;
    }

    display_books(books);

    int index;
    cout << "Введите индекс книги для удаления: ";
    cin >> index;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некорректный ввод! Попробуйте снова.\n";
        return;
    }

    if (index >= 0 && index < static_cast<int>(books.size())) {
        books.erase(books.begin() + index);
        cout << "Книга с индексом " << index << " удалена.\n";
    } else {
        cout << "Некорректный индекс! Попробуйте снова.\n";
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