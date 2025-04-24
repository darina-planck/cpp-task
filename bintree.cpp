#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// Структура для узла дерева
struct Node {
    int data;         // Значение узла
    Node* left;       // Указатель на левое поддерево
    Node* right;      // Указатель на правое поддерево

    // Конструктор для создания нового узла
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Функция для вставки нового значения в дерево
Node* insert(Node* root, int value) {
    // Если дерево пустое, создаем новый узел
    if (root == nullptr) {
        return new Node(value);
    }

    // Если значение меньше корня, вставляем в левое поддерево
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    // Иначе вставляем в правое поддерево
    else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Функция для определения высоты дерева
int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    // Высота дерева - это максимальная высота поддеревьев + 1
    return max(leftHeight, rightHeight) + 1;
}

// Эта функция удалена, так как мы оставляем только второй вариант представления

// Функция для вывода дерева наглядно с использованием псевдографики
void printTree(Node* root, string prefix = "", bool isLeft = false) {
    if (root == nullptr) {
        return;
    }

    // Сначала выводим правое поддерево (сверху)
    prettyPrintTree(root->right, prefix + (isLeft ? "│   " : "    "), false);

    // Затем выводим текущий узел
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << root->data << endl;

    // Затем выводим левое поддерево (снизу)
    prettyPrintTree(root->left, prefix + (isLeft ? "    " : "│   "), true);
}

// Функция для освобождения памяти, занятой деревом
void freeTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    // Рекурсивно освобождаем память для поддеревьев
    freeTree(root->left);
    freeTree(root->right);

    // Удаляем текущий узел
    delete root;
}

int main() {
    // Для корректной работы с русским языком
    setlocale(LC_ALL, "Russian");

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    // Запрашиваем количество чисел
    int N;
    cout << "Введите количество чисел (N): ";
    cin >> N;

    // Запрашиваем метод ввода чисел
    int method;
    cout << "Выберите метод ввода чисел:" << endl;
    cout << "1 - Ввод пользователем" << endl;
    cout << "2 - Генерация случайных чисел" << endl;
    cout << "Ваш выбор: ";
    cin >> method;

    // Инициализируем корень дерева
    Node* root = nullptr;

    // Заполняем дерево в зависимости от выбранного метода
    if (method == 1) {
        cout << "Введите " << N << " чисел:" << endl;
        for (int i = 0; i < N; i++) {
            int value;
            cout << "Число " << (i + 1) << ": ";
            cin >> value;
            root = insert(root, value);
        }
    } else if (method == 2) {
        cout << "Сгенерированные числа: ";
        for (int i = 0; i < N; i++) {
            int value = rand() % N + 1;  // Случайное число от 1 до N
            cout << value << " ";
            root = insert(root, value);
        }
        cout << endl;
    } else {
        cout << "Неверный выбор метода ввода!" << endl;
        return 1;
    }

    // Выводим дерево в консоль (простой иерархический вариант)
    cout << "\nСтруктура бинарного дерева (в консоли):" << endl;
    printTreeConsole(root);

    // Выводим высоту дерева
    cout << "\nВысота дерева: " << getHeight(root) << endl;

    // Автоматически сохраняем дерево в файл с красивым представлением
    string filename = "tree_output.txt";
    saveTreeToFile(root, filename);

    // Освобождаем память
    freeTree(root);

    return 0;
}