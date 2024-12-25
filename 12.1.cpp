#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

// Список цветов
const vector<char> colors = {'R', 'G', 'B', 'Y', 'P', 'O', 'W'}; // Красный, Зеленый, Синий, Желтый, Фиолетовый, Оранжевый, Белый

// Направления для поиска соседей: вверх, вниз, влево, вправо
const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Функция для получения ANSI-кода цвета текста
string getTextColorCode(char color) {
    if (color == 'R') return "\033[31m"; // Красный текст
    if (color == 'G') return "\033[32m"; // Зеленый текст
    if (color == 'B') return "\033[34m"; // Синий текст
    if (color == 'Y') return "\033[33m"; // Желтый текст
    if (color == 'P') return "\033[35m"; // Фиолетовый текст
    if (color == 'O') return "\033[33;1m"; // Голубой текст (заменяем оранжевый)
    if (color == 'W') return "\033[37m"; // Белый текст
    return "\033[30m"; // Черный текст (по умолчанию)
}

// нахождение областей одинакового цвета
// Определяет все области одинакового цвета, заполняя матрицу labels. Каждая область помечается уникальным числом (currentLabel)
void findAreas(const vector<vector<char>>& matrix, vector<vector<int>>& labels, int& currentLabel) {
    int N = matrix.size(); //  matrix - Матрица с цветами
    int M = matrix[0].size();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // Для каждой клетки проверяем, посещена ли она (метка -1).

            if (labels[i][j] == -1) { // labels - Матрица для пометок клеток областей. Изначально каждая клетка содержит -1 (не посещена)
                char color = matrix[i][j];
                // Присваиваем клетке текущую метку currentLabel.
                labels[i][j] = currentLabel; // currentLabel - Счетчик уникальных меток для каждой области

                bool changed = true;
                while (changed) {
                    changed = false;
                    // changed — это флаг, который указывает, изменилось ли состояние меток (labels) в текущей итерации.
                    // Если changed = true, это значит, что мы нашли новые клетки для добавления в область, и цикл должен продолжаться.
                    // Если changed = false, это значит, что больше нечего помечать, и цикл завершается.
                    for (int x = 0; x < N; ++x) {
                        for (int y = 0; y < M; ++y) {
                            if (labels[x][y] == currentLabel) { // Проверяем, относится ли эта клетка к текущей области (labels[x][y] == currentLabel)
                                for (const auto& [dx, dy] : directions) { // Проверка соседей текущей клетки
                                    int nx = x + dx, ny = y + dy;
                                    if (nx >= 0 && nx < N && ny >= 0 && ny < M && // проверка на то что сосед не за пределами матрицы и имеет один цвет
                                        labels[nx][ny] == -1 && matrix[nx][ny] == color) {
                                        // Помечаем её текущей меткой currentLabel.
                                        // Устанавливаем changed = true, чтобы цикл продолжился.
                                        labels[nx][ny] = currentLabel;
                                        changed = true;
                                    }
                                }
                            }
                        }
                    }
                }
                currentLabel++;
            }
        }
    }
}

int main() {
    // Генератор случайных чисел
    srand(static_cast<unsigned>(time(nullptr)));

    // Ввод размеров матрицы
    int N, M;
    cout << "Введите количество строк N: ";
    cin >> N;
    cout << "Введите количество столбцов M: ";
    cin >> M;

    // Генерация матрицы случайных цветов
    vector<vector<char>> matrix(N, vector<char>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = colors[rand() % colors.size()];
        }
    }

    // Вывод сгенерированной матрицы (текст цветной)
    cout << "\nСгенерированная матрица (текст цветной):\n";
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            cout << getTextColorCode(cell) << cell << " " << "\033[0m"; // Цвет текста + сброс
        }
        cout << '\n';
    }

    // Матрица для пометки областей
    vector<vector<int>> labels(N, vector<int>(M, -1));
    int currentLabel = 0;

    // Поиск областей
    findAreas(matrix, labels, currentLabel);

    // Считаем размеры областей
    vector<int> areaSizes(currentLabel, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (labels[i][j] != -1) {
                areaSizes[labels[i][j]]++;
            }
        }
    }

    // Находим максимальную область
    int maxSize = 0;
    for (int size : areaSizes) {
        if (size > maxSize) {
            maxSize = size;
        }
    }

    // Вывод областей максимального размера
    cout << "\nОбласти максимального размера (" << maxSize << " клеток):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (areaSizes[labels[i][j]] == maxSize) {
                cout << "Цвет: " << matrix[i][j] << ", Координаты: (" << i << ", " << j << ")\n";
            }
        }
    }

    return 0;
}
