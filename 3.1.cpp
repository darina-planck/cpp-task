#include <iostream>
#include <fstream> // Для работы с файлами

using namespace std;

int err(int n, int m)
{
    if (n < 0 || m < 0)
    {
        cout << "Неправильные входные данные." << "\n";
    }
    else if (n == 0 || m == 0)
    {
        cout << "Неправильные входные данные. Попробуйте еще раз." << "\n";
    }
    return 0;
}

int main()
{
    int n, u;
Step1:
    cout << "\n"
         << "Введите число и номер угла" << "\n";
    cin >> n >> u;

    cout << err(n, u);
    if (cin.fail()) // проверка на не число
    {
        cout << "Неправильные входные данные. Попробуйте еще раз.";
        cin.clear();
        cin.ignore();
        goto Step1;
    }
    ofstream outFile("snake.txt"); // создаю текстовый файл
    if (!outFile.is_open())
    {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1; // Завершаем программу, если не удалось открыть файл
    }
    long long a[n][n];
    int cur = 0;
    for (int c = 0; c < 2 * n; ++c)
    {
        if (c % 2 == 0) 
        { // если индекс диагонали чётный, то движение идет сверху вниз и слева направо.
            for (int i = 0; i < n; ++i)
            {
                int j = c - i;
                if (0 <= j && j < n)
                {
                    cur++;
                    if (u == 1) // Заполнение начинается с верхнего левого угла.
                    {
                        a[i][j] = cur;
                    }
                    else if (u == 2) // начинается с верхнего правого угла
                    {
                        a[i][n - 1 - j] = cur;
                    }
                    else if (u == 3) // начинается с нижнего левого угла
                    {
                        a[n - 1 - i][j] = cur;
                    }
                    else if (u == 4) // начинается с нижнего правого угла
                    {
                        a[n - 1 - i][n - 1 - j] = cur;
                    }
                }
            }
        }
        else
        { // если индекс диагонали нечётный — снизу вверх.
            for (int i = n - 1; i >= 0; i--)
            {
                int j = c - i;
                if (0 <= j && j < n)
                {
                    cur++;
                    if (u == 1)
                    {
                        a[i][j] = cur;
                    }
                    else if (u == 2)
                    {
                        a[i][n - 1 - j] = cur;
                    }
                    else if (u == 3)
                    {
                        a[n - 1 - i][j] = cur;
                    }
                    else if (u == 4)
                    {
                        a[n - 1 - i][n - 1 - j] = cur;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
    { // вывод в файл
        {
            for (int j = 0; j < n; ++j)
                outFile << a[i][j] << "\t";
            outFile << endl;
        }
    }
}