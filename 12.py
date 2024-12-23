import random

# Список из 7 разных цветов, каждый цвет представлен символом
colors = ['R', 'G', 'B', 'Y', 'P', 'O', 'V']  # Красный, Зеленый, Синий, Желтый, Фиолетовый, Оранжевый, Белый

# Направления для поиска соседей: вверх, вниз, влево, вправо
directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Поиск по 4 сторонам

# Функция для поиска области одинакового цвета с помощью DFS
def dfs(matrix, visited, x, y, color, N, M):
    stack = [(x, y)]
    area = []
    while stack:
        cx, cy = stack.pop()
        if 0 <= cx < N and 0 <= cy < M and not visited[cx][cy] and matrix[cx][cy] == color:
            visited[cx][cy] = True
            area.append((cx, cy))
            # Проверяем все соседние клетки
            for dx, dy in directions:
                nx, ny = cx + dx, cy + dy
                if 0 <= nx < N and 0 <= ny < M and not visited[nx][ny] and matrix[nx][ny] == color:
                    stack.append((nx, ny))
    return area

# Основная функция
def main():
    # Ввод размеров матрицы
    N = int(input("Введите количество строк N: "))
    M = int(input("Введите количество столбцов M: "))

    # Генерация матрицы случайных цветов
    matrix = [[random.choice(colors) for _ in range(M)] for _ in range(N)]

    # Вывод сгенерированной матрицы
    print("\nСгенерированная матрица:")
    for row in matrix:
        print(' '.join(row))

    # Массив для отслеживания посещенных клеток
    visited = [[False] * M for _ in range(N)]

    # Переменные для хранения наибольшей области
    max_area = []
    max_area_size = 0

    # Поиск наибольшей области одинакового цвета
    for i in range(N):
        for j in range(M):
            if not visited[i][j]:
                area = dfs(matrix, visited, i, j, matrix[i][j], N, M)
                if len(area) > max_area_size:
                    max_area = area
                    max_area_size = len(area)

    # Вывод наибольшей области
    print(f"\nНаибольшая область одинакового цвета (размер: {max_area_size}):")
    for x, y in max_area:
        print(f"({x}, {y}) -> {matrix[x][y]}")

if __name__ == "__main__":
    main()
