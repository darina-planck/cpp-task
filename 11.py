import os

def load_books(file_path):
    """Загружает книги из файла."""
    books = []
    if os.path.exists(file_path):
        with open(file_path, 'r', encoding='utf-8') as file:
            for line in file:
                parts = line.strip().split()
                if len(parts) >= 5:
                    title = ' '.join(parts[:-4])
                    author, publisher, year, price = parts[-4:]
                    books.append((title, author, publisher, int(year), float(price)))
    return books

def save_books(file_path, books):
    """Сохраняет книги в файл."""
    with open(file_path, 'w', encoding='utf-8') as file:
        for book in books:
            file.write(f"{' '.join(map(str, book))}\n")

def display_books(books):
    """Отображает книги в табличном формате."""
    print(f"{'Название':<20} {'Автор':<15} {'Издательство':<15} {'Год':<5} {'Цена':<10}")
    print("-" * 70)
    for title, author, publisher, year, price in books:
        print(f"{title:<20} {author:<15} {publisher:<15} {year:<5} {price:<10.2f}")

def filter_books_by_price(books, min_price, max_price):
    """Фильтрует книги по диапазону цен."""
    return [book for book in books if min_price <= book[4] <= max_price]

def add_book(books):
    """Добавляет новую книгу."""
    title = input("Введите название книги: ")
    author = input("Введите автора книги: ")
    publisher = input("Введите издательство книги: ")
    year = int(input("Введите год издания книги: "))
    price = float(input("Введите цену книги: "))
    books.append((title, author, publisher, year, price))

def delete_book(books):
    """Удаляет книгу по индексу."""
    display_books(books)
    index = int(input("Введите индекс книги для удаления: "))
    if 0 <= index < len(books):
        books.pop(index)
    else:
        print("Некорректный индекс!")

def merge_books(file_path, books):
    """Добавляет книги из другого файла."""
    other_file = input("Введите путь к другому файлу: ")
    if os.path.exists(other_file):
        other_books = load_books(other_file)
        books.extend(other_books)
    else:
        print("Файл не найден!")

def main():
    file_path = input("Введите путь к файлу с книгами: ")
    books = load_books(file_path)

    while True:
        print("\nМеню:")
        print("1. Показать книги")
        print("2. Показать книги в диапазоне цен")
        print("3. Добавить книгу")
        print("4. Удалить книгу")
        print("5. Объединить с другим файлом")
        print("6. Сохранить и выйти")

        choice = input("Выберите действие: ")

        if choice == '1':
            display_books(books)
        elif choice == '2':
            min_price = float(input("Введите минимальную цену: "))
            max_price = float(input("Введите максимальную цену: "))
            filtered_books = filter_books_by_price(books, min_price, max_price)
            display_books(filtered_books)
        elif choice == '3':
            add_book(books)
        elif choice == '4':
            delete_book(books)
        elif choice == '5':
            merge_books(file_path, books)
        elif choice == '6':
            save_books(file_path, books)
            print("Данные сохранены. Выход из программы.")
            break
        else:
            print("Некорректный выбор!")

if __name__ == "__main__":
    main()
