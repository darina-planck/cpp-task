#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для распределения вещей по K рюкзакам с минимальной разницей в весах
void distribute_items(int K, vector<int>& weights) {
    int N = weights.size();

    // Рассортируем вещи по убыванию веса
    sort(weights.rbegin(), weights.rend());

    // Массив для хранения текущего веса каждого рюкзака
    vector<int> rucksack_weights(K, 0);

    // Распределяем вещи по рюкзакам с наименьшим текущим весом
    for (int i = 0; i < N; ++i) {
        // Находим рюкзак с минимальным текущим весом
        int min_weight_idx = min_element(rucksack_weights.begin(), rucksack_weights.end()) - rucksack_weights.begin();
        // Добавляем вещь в этот рюкзак
        rucksack_weights[min_weight_idx] += weights[i];
    }

    // Выводим вес каждого рюкзака
    cout << "Распределение вещей по рюкзакам:" << endl;
    for (int i = 0; i < K; ++i) {
        cout << "Рюкзак " << i + 1 << " (вес = " << rucksack_weights[i] << ")" << endl;
    }
}

int main() {
    int N, K;

    // Ввод количества вещей и числа рюкзаков
    cout << "Введите количество вещей: ";
    cin >> N;
    cout << "Введите количество рюкзаков (K): ";
    cin >> K;

    vector<int> weights(N);
    for (int i = 0; i < N; ++i) {
        cout << "Введите вес вещи " << i + 1 << ": ";
        cin >> weights[i];
    }

    // Проверяем возможность распределения вещей по K рюкзакам
    distribute_items(K, weights);

    return 0;
}
