#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

// Список цветов
const vector<char> colors = {'R', 'G', 'B', 'Y', 'P', 'O', 'V'}; // Красный, Зеленый, Синий, Желтый, Фиолетовый, Оранжевый, Белый

// Направления для поиска соседей: вверх, вниз, влево, вправо
const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Функция для поиска области одинакового цвета с помощью DFS
void dfs(const vector<vector<char>>& matrix, vector<vector<bool>>& visited, int x, int y, char color, vector<pair<int, int>>& area) {
    int N = matrix.size();
    int M = matrix[0].size();
    stack<pair<int, int>> toVisit; // Стек для координат

    toVisit.push({x, y});

    while (!toVisit.empty()) {
        auto [cx, cy] = toVisit.top();
        toVisit.pop();

        // Проверяем границы и уже посещенные клетки
        if (cx < 0 || cx >= N || cy < 0 || cy >= M || visited[cx][cy] || matrix[cx][cy] != color) {
            continue;
        }

        visited[cx][cy] = true;
        area.push_back({cx, cy});

        // Добавляем соседей в стек
        for (const auto& [dx, dy] : directions) {
            int nx = cx + dx;
            int ny = cy + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && matrix[nx][ny] == color) {
                toVisit.push({nx, ny});
            }
        }
    }
}

int main() {
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

    // Вывод сгенерированной матрицы
    cout << "\nСгенерированная матрица:\n";
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }

    // Массив для отслеживания посещенных клеток
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    // Список всех областей и их размеров
    vector<vector<pair<int, int>>> all_areas;

    // Поиск всех областей одинакового цвета
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!visited[i][j]) {
                vector<pair<int, int>> area;
                dfs(matrix, visited, i, j, matrix[i][j], area);
                all_areas.push_back(area);
            }
        }
    }

    // Находим максимальный размер области
    int max_size = 0;
    for (const auto& area : all_areas) {
        if (area.size() > max_size) {
            max_size = area.size();
        }
    }

    // Вывод всех областей максимального размера
    cout << "\nОбласти максимального размера (" << max_size << " клеток):\n";
    for (const auto& area : all_areas) {
        if (area.size() == max_size) {
            cout << "Цвет: " << matrix[area[0].first][area[0].second] 
                 << ", Координаты: ";
            for (const auto& [x, y] : area) {
                cout << "(" << x << ", " << y << ") ";
            }
            cout << '\n';
        }
    }

    return 0;
}
