#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <ctime>
using namespace std;

// Функция для слияния двух отсортированных подмассивов
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные подмассивы
    vector<int> L(n1), R(n2);

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Слияние временных массивов обратно в arr[left..right]
    int i = 0;    // Индекс первого подмассива
    int j = 0;    // Индекс второго подмассива
    int k = left; // Индекс объединенного массива

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы L[], если они есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R[], если они есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Функция сортировки слиянием
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находим середину массива
        int mid = left + (right - left) / 2;

        // Сортируем первую и вторую половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Объединяем отсортированные половины
        merge(arr, left, mid, right);
    }
}

// Функция шейкерной сортировки
void shakerSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {
        // Сбрасываем флаг обмена на каждой итерации
        swapped = false;

        // Проход слева направо (как в сортировке пузырьком)
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // Если не было обменов, массив отсортирован
        if (!swapped)
            break;

        // В противном случае сбрасываем флаг обмена для прохода справа налево
        swapped = false;
        
        // Перемещаем конечную точку на один назад
        --end;

        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // Увеличиваем начальную точку, так как наименьший элемент
        // уже находится на своей позиции
        ++start;
    }
}

// Функция для записи вектора в файл
void writeToFile(const vector<int>& arr, const std::string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return;
    }

    for (const auto& num : arr) {
        outFile << num << " ";
    }
    outFile.close();
}

int main() {
    std::vector<int> numbers;
    char choice;
    
    // Настраиваем вывод на русском языке
    setlocale(LC_ALL, "Russian");
    
    // Создаем имена файлов с временной меткой для уникальности
    time_t now = time(0);
    std::string timestamp = std::to_string(now);
    std::string initialFileName = "исходный_файл_" + timestamp + ".txt";
    std::string mergeSortFileName = "отсортированный_слиянием_" + timestamp + ".txt";
    std::string shakerSortFileName = "отсортированный_шейкером_" + timestamp + ".txt";

    std::cout << "Как вы хотите заполнить список чисел?" << std::endl;
    std::cout << "1. Ввести самостоятельно" << std::endl;
    std::cout << "2. Сгенерировать случайно" << std::endl;
    std::cout << "Ваш выбор (1/2): ";
    std::cin >> choice;

    if (choice == '1') {
        int n, num;
        std::cout << "Введите количество чисел: ";
        std::cin >> n;
        
        std::cout << "Введите " << n << " чисел:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cin >> num;
            numbers.push_back(num);
        }
    } else if (choice == '2') {
        int count, min_value, max_value;
        
        std::cout << "Введите количество чисел: ";
        std::cin >> count;
        
        std::cout << "Введите минимальное значение: ";
        std::cin >> min_value;
        
        std::cout << "Введите максимальное значение: ";
        std::cin >> max_value;

        // Генерируем случайные числа
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min_value, max_value);

        for (int i = 0; i < count; i++) {
            numbers.push_back(distrib(gen));
        }
    } else {
        std::cout << "Некорректный выбор. Завершение программы." << std::endl;
        return 1;
    }

    // Записываем исходный список в файл
    writeToFile(numbers, initialFileName);
    cout << "Исходный список сохранен в файл: " << initialFileName << endl;

    // Создаем копии для двух методов сортировки
    vector<int> mergeSortNumbers = numbers;
    vector<int> shakerSortNumbers = numbers;

    // Выполняем сортировку слиянием
    mergeSort(mergeSortNumbers, 0, mergeSortNumbers.size() - 1);
    
    // Выполняем шейкерную сортировку
    shakerSort(shakerSortNumbers);

    // Записываем отсортированные списки в файлы
    writeToFile(mergeSortNumbers, mergeSortFileName);
    writeToFile(shakerSortNumbers, shakerSortFileName);

    cout << "Список, отсортированный методом слияния, сохранен в файл: " << mergeSortFileName << endl;
    cout << "Список, отсортированный шейкерным методом, сохранен в файл: " << shakerSortFileName << endl;

    return 0;
}