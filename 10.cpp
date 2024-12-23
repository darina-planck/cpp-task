#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> distribute_items_dp(vector<int>& items, int K) {
    int total_weight = 0;
    for (int item : items) {
        total_weight += item;
    }
    int target_weight = total_weight / K;
    int n = items.size();

    // Инициализируем матрицу для динамического программирования
    vector<vector<bool>> dp(n + 1, vector<bool>(target_weight + 1, false));
    dp[0][0] = true;

    // Заполняем матрицу
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= target_weight; ++w) {
            dp[i][w] = dp[i-1][w];
            if (w >= items[i-1]) {
                dp[i][w] = dp[i][w] || dp[i-1][w - items[i-1]];
            }
        }
    }

    // Находим максимальный вес, который можно собрать
    int max_weight = 0;
    for (int w = 0; w <= target_weight; ++w) {
        if (dp[n][w]) {
            max_weight = w;
        }
    }

    // Восстанавливаем набор вещей для первого рюкзака
    vector<int> backpack1;
    int w = max_weight;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] && !dp[i-1][w]) {
            backpack1.push_back(items[i-1]);
            w -= items[i-1];
        }
    }

    // Оставшиеся вещи идут во второй рюкзак
    vector<int> backpack2;
    for (int item : items) {
        if (find(backpack1.begin(), backpack1.end(), item) == backpack1.end()) {
            backpack2.push_back(item);
        }
    }

    return {backpack1, backpack2};
}

int main() {
    int N, K;
    cout << "Введите количество вещей: ";
    cin >> N;

    vector<int> items(N);
    for (int i = 0; i < N; ++i) {
        cout << "Введите вес вещи " << i + 1 << ": ";
        cin >> items[i];
    }

    cout << "Введите количество рюкзаков: ";
    cin >> K;

    // Распределяем вещи по рюкзакам
    vector<vector<int>> backpacks = distribute_items_dp(items, K);

    // Выводим результат
    cout << "Распределение вещей по рюкзакам:" << endl;
    for (int i = 0; i < backpacks.size(); ++i) {
        int weight = 0;
        for (int item : backpacks[i]) {
            weight += item;
        }
        cout << "Рюкзак " << i + 1 << ": " << weight << " кг" << endl;
        cout << "Вещи: ";
        for (int item : backpacks[i]) {
            cout << item << " ";
        }
        cout << endl;
    }

    return 0;
}
